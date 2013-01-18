#include "core_pch.h"
#include "..\..\include\core\RenderSystem.h"
#include "core\RenderData.h"
#include "core\Sys_Graphics.h"
#include "core\Material.h"
#include "core\g_format.h"
#include "core\RenderTarget.h"
#include "core_utils.h"
#include "core\GPUBuffer.h"
#include "core\LightManager.h"
#include "core\Light.h"
#include "core\PostEffectManager.h"
#include "core\Camera.h"

namespace ld3d
{
	RenderSystem::RenderSystem(void)
	{
		m_viewMatrix.MakeIdentity();
		m_projMatrix.MakeIdentity();

		m_clearClr						= math::Color4(0.0f, 0.2f, 0.3f, 1.0f);
		m_clearDepth					= 1.0f;
		m_clearStencil					= 0;
		m_globalAmbientColor			= math::Color4(0.3f, 0.3f, 0.3f, 1.0f);

	}


	RenderSystem::~RenderSystem(void)
	{
	}

	bool RenderSystem::Initialize(Sys_GraphicsPtr pGraphics)
	{
		m_pGraphics = pGraphics;

		int w = pGraphics->GetFrameBufferWidth();
		int h = pGraphics->GetFrameBufferHeight();

		if(false == CreateGBuffer(w, h))
		{
			return false;
		}
		if(false == CreateABuffer(w, h))
		{
			return false;
		}

		m_pScreenQuad = alloc_object<ScreenQuad>();
		if(m_pScreenQuad->Init(m_pGraphics) == false)
		{
			return false;
		}

		m_pLightManager = alloc_object<LightManager>();
		if(m_pLightManager->Initialize(shared_from_this()) == false)
		{
			return false;
		}

		m_pPostEffectManager = alloc_object<PostEffectManager>();
		if(m_pPostEffectManager->Initialize(shared_from_this()) == false)
		{
			return false;
		}

		m_pScreenQuadMaterial = pGraphics->CreateMaterialFromFile("./assets/standard/material/dr_render_merge.fx");
		//m_pScreenQuadMaterial = CreateMaterialFromFile("./assets/standard/material/dr_render_ssao.fx");

		VertexElement vf[] = 
		{
			VertexElement(0, VertexElement::POSITION,G_FORMAT_R32G32B32_FLOAT),
		};
		VertexFormat format;

		format.SetElement(vf, 1);

		m_pScreenQuadMaterial->SetVertexFormat(format);

		
		return true;
	}
	bool RenderSystem::CreateGBuffer(int w, int h)
	{
		if(m_pGBuffer != nullptr)
		{
			m_pGBuffer->Release();
			m_pGBuffer.reset();
		}

		G_FORMAT formats[3] = 
		{
			G_FORMAT_R16G16B16A16_FLOAT,				// position
			G_FORMAT_R16G16B16A16_FLOAT,				// normal
			G_FORMAT_R16G16B16A16_FLOAT,				// diffuse color : specular
		};

		m_pGBuffer = CreateRenderTarget(3, w, h, formats);

		return true;

	}
	void RenderSystem::Release()
	{
		Clear();

		if(m_pScreenQuadMaterial)
		{
			m_pScreenQuadMaterial->Release();
			m_pScreenQuadMaterial.reset();
		}
		if(m_pLightManager)
		{
			m_pLightManager->Release();
			m_pLightManager.reset();
		}

		if(m_pPostEffectManager)
		{
			m_pPostEffectManager->Release();
			m_pPostEffectManager.reset();
		}
		if(m_pScreenQuad)
		{
			m_pScreenQuad->Release();
			m_pScreenQuad.reset();
		}
		if(m_pGBuffer != nullptr)
		{
			m_pGBuffer->Release();
			m_pGBuffer.reset();
		}
		if(m_pABuffer != nullptr)
		{
			m_pABuffer->Release();
			m_pABuffer.reset();
		}
	}

	void RenderSystem::AddRenderData(RenderDataPtr pData)
	{
		if(pData->IsDeferred())
		{
			m_deferredQueue.push_back(pData);
		}
		else
		{
			m_forwardQueue.push_back(pData);
		}
	}
	void RenderSystem::Clear()
	{
		m_forwardQueue.clear();
		m_deferredQueue.clear();
		m_transparentQueue.clear();
	}
	void RenderSystem::DR_G_Pass()
	{
		m_pGraphics->SetRenderTarget(m_pGBuffer);
		m_pGraphics->ClearRenderTarget(m_pGBuffer, 0, math::Color4(0, 0, 0, 1));
		m_pGraphics->ClearRenderTarget(m_pGBuffer, 1, math::Color4(0, 0, 0, 0));
		m_pGraphics->ClearRenderTarget(m_pGBuffer, 2, math::Color4(0, 0, 0, 1));
		m_pGraphics->ClearDepthStencilBuffer(DepthStencilBufferPtr(), CLEAR_ALL, 1.0f, 0);


		for(size_t i = 0; i < m_deferredQueue.size(); ++i)
		{
			SetSemanticsValue(m_deferredQueue[i]);
			
			m_deferredQueue[i]->Render(m_pGraphics);
		}

	}
	void RenderSystem::DR_Merge_Pass()
	{
		RenderTargetPtr pOutput = m_pPostEffectManager->GetInput();

		m_pGraphics->SetRenderTarget(pOutput);
		m_pGraphics->ClearRenderTarget(pOutput, 0, m_clearClr);

		m_pScreenQuadMaterial->SetGBuffer(m_pGBuffer);
		m_pScreenQuadMaterial->SetABuffer(m_pABuffer);
		m_pScreenQuadMaterial->SetProjMatrix(m_projMatrix);
		m_pScreenQuadMaterial->SetViewMatrix(m_viewMatrix);
		m_pScreenQuadMaterial->SetWorldMatrix(math::MatrixIdentity());

		DrawFullScreenQuad(m_pScreenQuadMaterial);
	}
	void RenderSystem::RenderForward()
	{
		for(size_t i = 0; i < m_forwardQueue.size(); ++i)
		{
			SetSemanticsValue(m_forwardQueue[i]);
			
			m_forwardQueue[i]->Render(m_pGraphics);
		}

		for(size_t i = 0; i < m_transparentQueue.size(); ++i)
		{
			SetSemanticsValue(m_transparentQueue[i]);
			
			m_transparentQueue[i]->Render(m_pGraphics);
		}
	}
	void RenderSystem::Render(CameraPtr pCamera)
	{
		SetViewMatrix(pCamera->GetViewMatrix());
		SetProjMatrix(pCamera->GetProjMatrix());

		RenderShadowMaps();

		DR_G_Pass();
		DR_Light_Pass();
		DR_Merge_Pass();
		
		RenderForward();

		RenderPostEffects();
		
		RenderFinal();
		
	}
	void RenderSystem::Render()
	{
		m_cameras.sort(Camera::SortFunction);

		std::list<CameraPtr>::iterator it = m_cameras.begin();
		for(it; it != m_cameras.end(); ++it)
		{
			Render(*it);
		}
	}
	void RenderSystem::Present()
	{
		m_pGraphics->Present();
	}
	void RenderSystem::SetViewMatrix(const math::Matrix44& view)
	{
		m_viewMatrix = view;
	}
	void RenderSystem::SetProjMatrix(const math::Matrix44& proj)
	{
		m_projMatrix = proj;
	}
	void RenderSystem::SetSemanticsValue(RenderDataPtr pData)
	{
		MaterialPtr pMaterial = pData->GetMaterial();
		math::Matrix44 world = pData->GetWorldMatrix();
		pMaterial->SetProjMatrix(m_projMatrix);
		pMaterial->SetViewMatrix(m_viewMatrix);
		pMaterial->SetWorldMatrix(world);
	}
	Sys_GraphicsPtr	RenderSystem::GetSysGraphics()
	{
		return m_pGraphics;
	}
	void RenderSystem::SetClearColor(const math::Color4& clr)
	{
		m_clearClr	 = clr;
	}
	const math::Color4&	RenderSystem::GetClearColor()
	{
		return m_clearClr;
	}
	void RenderSystem::SetClearDepth(float d)
	{
		m_clearDepth = d;
	}
	void RenderSystem::SetClearStencil(int s)
	{
		m_clearStencil = s;
	}
	void RenderSystem::ResizeFrameBuffer(int cx, int cy)
	{
		if(cx == 0 || cy == 0)
		{
			return;
		}

		m_pGraphics->SetRenderTarget(ld3d::RenderTargetPtr());

		m_pGraphics->ResizeFrameBuffer(cx, cy);
		

		CreateGBuffer(cx, cy);
		CreateABuffer(cx, cy);

		m_pPostEffectManager->Resize(cx, cy);
	}
	void RenderSystem::AddLight(LightPtr pLight)
	{
		m_pLightManager->AddLight(pLight);
	}
	void RenderSystem::RemoveLight(LightPtr pLight)
	{
		m_pLightManager->RemoveLight(pLight);
	}
	int	RenderSystem::GetLightCount()
	{
		return m_pLightManager->GetLightCount();
	}
	
	void RenderSystem::DR_Light_Pass()
	{
		m_pGraphics->SetRenderTarget(m_pABuffer);

		math::Color4 clr = m_globalAmbientColor;
		clr.a = 0;

		m_pGraphics->ClearRenderTarget(m_pABuffer, 0, clr);

		m_pLightManager->RenderLights();
	}
	void RenderSystem::RenderShadowMaps()
	{
		LightPtr pLight = m_pLightManager->GetNextAffectingLight(LightPtr(), ViewFrustum());
		while(pLight)
		{
			if(pLight->GetCastShadow() == true)
			{
				pLight->RenderShadowMap();
			}
			pLight = m_pLightManager->GetNextAffectingLight(pLight, ViewFrustum());
		}
	}
	
	bool RenderSystem::CreateABuffer(int w, int h)
	{
		if(m_pABuffer != nullptr)
		{
			m_pABuffer->Release();
			m_pABuffer.reset();
		}

		G_FORMAT formats[1] = {G_FORMAT_R8G8B8A8_UNORM,};
		m_pABuffer = CreateRenderTarget(1, w, h, formats);

		return true;
	}
	RenderTargetPtr RenderSystem::GetGBuffer()
	{
		return m_pGBuffer;
	}
	RenderTargetPtr RenderSystem::GetABuffer()
	{
		return m_pABuffer;
	}
	const math::Matrix44& RenderSystem::GetViewMatrix()
	{
		return m_viewMatrix;
	}
	const math::Matrix44& RenderSystem::GetProjMatrix()
	{
		return m_projMatrix;
	}
	void RenderSystem::DrawFullScreenQuad(MaterialPtr pMaterial)
	{
		m_pScreenQuad->Render(m_pGraphics, pMaterial);
	}
}







namespace ld3d
{
	bool RenderSystem::ScreenQuad::Init(Sys_GraphicsPtr pGraphics)
	{
		math::Vector3 verts[] = 
		{
			math::Vector3(-1, 1, 0),
			math::Vector3(1, 1, 0),
			math::Vector3(1, -1, 0),
			math::Vector3(-1, 1, 0),
			math::Vector3(1, -1, 0),
			math::Vector3(-1, -1, 0),
		};

		m_pVB = pGraphics->CreateBuffer(BT_VERTEX_BUFFER, sizeof(math::Vector3) * 6, verts, true);

		return true;
	}
	void RenderSystem::ScreenQuad::Release()
	{
		if(m_pVB)
		{
			m_pVB->Release();
			m_pVB.reset();
		}
	}
	void RenderSystem::ScreenQuad::Render(Sys_GraphicsPtr pGraphics, MaterialPtr pMaterial)
	{
		pGraphics->SetVertexBuffer(m_pVB, 0, sizeof(math::Vector3));
		pGraphics->SetPrimitiveType(PT_TRIANGLE_LIST);

		pMaterial->ApplyVertexFormat();

		int nPass = 0;

		pMaterial->Begin(nPass);

		for(int i = 0; i < nPass; ++i)
		{
			pMaterial->ApplyPass(i);
			pGraphics->Draw(6, 0);
		}

		pMaterial->End();
	}
	const math::Color4& RenderSystem::GetGlobalAmbient()
	{
		return m_globalAmbientColor;
	}
	void RenderSystem::SetGlobalAmbient(const math::Color4& clr)
	{
		m_globalAmbientColor = clr;
	}
	void RenderSystem::SetRenderTarget(RenderTargetPtr pRT)
	{
		m_pGraphics->SetRenderTarget(pRT);
	}
	void RenderSystem::ClearRenderTarget(RenderTargetPtr pRT, int index, const math::Color4 & clr)
	{
		m_pGraphics->ClearRenderTarget(pRT, index, clr);
	}
	void RenderSystem::ClearDepthBuffer(DepthStencilBufferPtr pDS, CLEAR_DS_FLAG flag, float d, int s)
	{
		m_pGraphics->ClearDepthStencilBuffer(pDS, flag, d, s);
	}
	RenderTargetPtr	RenderSystem::CreateRenderTarget(int c, int w, int h, G_FORMAT format[])
	{
		return m_pGraphics->CreateRenderTarget(c, w, h, format);
	}
	int	RenderSystem::GetFrameBufferWidth()
	{
		return m_pGraphics->GetFrameBufferWidth();
	}
	int	RenderSystem::GetFrameBufferHeight()
	{
		return m_pGraphics->GetFrameBufferHeight();
	}
	void RenderSystem::RenderPostEffects()
	{
		m_pPostEffectManager->Render();
	}
	void RenderSystem::RenderFinal()
	{
		m_pPostEffectManager->RenderToFrameBuffer();
	}
	MaterialPtr	RenderSystem::CreateMaterialFromFile(const char* szFile)
	{
		return m_pGraphics->CreateMaterialFromFile(szFile);
	}
	TexturePtr RenderSystem::CreateTextureFromFile(const char* szFile)
	{
		return m_pGraphics->CreateTextureFromFile(szFile);
	}
	void RenderSystem::AddPostEffect(PostEffectPtr pEffect)
	{
		m_pPostEffectManager->AddEffect(pEffect);
	}
	void RenderSystem::AddCamera(CameraPtr pCamera)
	{
		m_cameras.push_back(pCamera);
	}
	void RenderSystem::RemoveCamera(CameraPtr pCamera)
	{
		m_cameras.remove(pCamera);
	}
}
