#include "core_pch.h"
#include "..\..\include\core\RenderSystem.h"
#include "core\RenderData.h"
#include "core\Sys_Graphics.h"
#include "core\Material.h"
#include "core\g_format.h"
#include "core\MultiRenderTarget.h"
#include "core_utils.h"
#include "core\GPUBuffer.h"
#include "core\LightManager.h"
#include "core\Light.h"
#include "core\RenderTarget.h"

namespace engine
{
	RenderSystem::RenderSystem(void)
	{
		m_viewMatrix.MakeIdentity();
		m_projMatrix.MakeIdentity();

		m_clearClr						= math::Color4(0.0f, 0.2f, 0.3f, 1.0f);
		m_clearDepth					= 1.0f;
		m_clearStencil					= 0;
	}


	RenderSystem::~RenderSystem(void)
	{
	}

	bool RenderSystem::Initialize(Sys_GraphicsPtr pGraphics)
	{
		m_pGraphics = pGraphics;

		if(false == CreateGBuffer())
		{
			return false;
		}
		if(false == CreateABuffer())
		{
			return false;
		}

		m_pScreenQuad = alloc_object<ScreenQuad>();
		if(m_pScreenQuad->Init(m_pGraphics) == false)
		{
			return false;
		}

		m_pLightManager = alloc_object<LightManager>();
		if(m_pLightManager->Initialize(m_pGraphics) == false)
		{
			return false;
		}

		m_pScreenQuadMaterial = pGraphics->CreateMaterialFromFile("./assets/material/dr_render_final_merge.fx");

		VertexElement vf[] = 
		{
			VertexElement(0, VertexElement::POSITION,G_FORMAT_R32G32B32_FLOAT),
			VertexElement(0, VertexElement::TEXCOORD,G_FORMAT_R32G32_FLOAT),
		};
		VertexFormat format;

		format.SetElement(vf, 2);

		m_pScreenQuadMaterial->SetVertexFormat(format);
		
		return true;
	}
	bool RenderSystem::CreateGBuffer()
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

		const GraphicsSetting& setting = m_pGraphics->GetGraphicsSetting();

		m_pGBuffer = m_pGraphics->CreateMultiRenderTarget(3, setting.frameBufferWidth, setting.frameBufferHeight, formats);

		return true;

	}
	void RenderSystem::Release()
	{
		m_forwardQueue.clear();
		m_deferredQueue.clear();

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
	}
	void RenderSystem::RenderGBuffer()
	{
		m_pGraphics->SetRenderTarget(m_pGBuffer);
		m_pGraphics->ClearRenderTarget(m_pGBuffer->GetRenderTarget(0), math::Color4(0, 0, 0, 1));
		m_pGraphics->ClearRenderTarget(m_pGBuffer->GetRenderTarget(1), math::Color4(0, 0, 0, 0));
		m_pGraphics->ClearRenderTarget(m_pGBuffer->GetRenderTarget(2), math::Color4(0, 0, 0, 1));
		m_pGraphics->ClearDepthStencilBuffer(DepthStencilBufferPtr(), CLEAR_ALL, 1.0f, 0);


		for(size_t i = 0; i < m_deferredQueue.size(); ++i)
		{
			SetSemanticsValue(m_deferredQueue[i]);
			
			m_deferredQueue[i]->Render(m_pGraphics);
		}

	}
	void RenderSystem::RenderScreenQuad()
	{
		m_pGraphics->SetRenderTarget(RenderTargetPtr());
		m_pGraphics->ClearRenderTarget(RenderTargetPtr(), m_clearClr);


		m_pScreenQuadMaterial->SetGBuffer(m_pGBuffer);
		m_pScreenQuadMaterial->SetABuffer(m_pABuffer);
		m_pScreenQuadMaterial->SetProjMatrix(m_projMatrix);
		m_pScreenQuadMaterial->SetViewMatrix(m_viewMatrix);
		m_pScreenQuadMaterial->SetWorldMatrix(math::MatrixIdentity());

		math::Vector2 vp = math::Vector2(m_pGraphics->GetGraphicsSetting().frameBufferWidth, m_pGraphics->GetGraphicsSetting().frameBufferHeight);
		m_pScreenQuadMaterial->SetVectorBySemantic("VP_SIZE", vp);

		m_pScreenQuad->Render(m_pGraphics, m_pScreenQuadMaterial);
	}
	void RenderSystem::RenderForward()
	{
		for(size_t i = 0; i < m_forwardQueue.size(); ++i)
		{
			SetSemanticsValue(m_forwardQueue[i]);
			
			m_forwardQueue[i]->Render(m_pGraphics);
		}
	}
	void RenderSystem::Render()
	{
		RenderShadowMaps();

		RenderGBuffer();
		RenderLights();
		RenderScreenQuad();
		RenderForward();

		MergeOutput();
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

		m_pGraphics->ResizeFrameBuffer(cx, cy);
		m_pGraphics->SetRenderTarget(engine::RenderTargetPtr());

		CreateGBuffer();
		CreateABuffer();
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
	
	void RenderSystem::RenderLights()
	{
		m_pGraphics->SetRenderTarget(m_pABuffer);
		m_pGraphics->ClearRenderTarget(m_pABuffer, math::Color4(0, 0, 0, 0));

		m_pLightManager->GetLightMaterial()->SetWorldMatrix(math::MatrixIdentity());
		m_pLightManager->GetLightMaterial()->SetViewMatrix(m_viewMatrix);
		m_pLightManager->GetLightMaterial()->SetProjMatrix(m_projMatrix);

		m_pLightManager->RenderLights(m_pGBuffer);
	}
	void RenderSystem::RenderShadowMaps()
	{
		LightPtr pLight = m_pLightManager->GetNextAffectingLight(LightPtr(), ViewFrustum());
		while(pLight)
		{
			pLight->RenderShadowMap();
			pLight = m_pLightManager->GetNextAffectingLight(pLight, ViewFrustum());
		}
	}
	void RenderSystem::MergeOutput()
	{
	}
	bool RenderSystem::CreateABuffer()
	{
		if(m_pABuffer != nullptr)
		{
			m_pABuffer->Release();
			m_pABuffer.reset();
		}

		const GraphicsSetting& setting = m_pGraphics->GetGraphicsSetting();

		m_pABuffer = m_pGraphics->CreateRenderTarget(setting.frameBufferWidth, setting.frameBufferHeight, G_FORMAT_R16G16B16A16_FLOAT);

		return true;
	}
}







namespace engine
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
}
