#include "core_pch.h"
#include "..\..\include\core\RenderSystem.h"
#include "core\RenderData.h"
#include "core\Sys_Graphics.h"
#include "core\Material.h"
#include "core\g_format.h"
#include "core\MultiRenderTarget.h"
#include "core_utils.h"
#include "core\GPUBuffer.h"

namespace engine
{
	RenderSystem::RenderSystem(void)
	{
		m_viewMatrix.MakeIdentity();
		m_projMatrix.MakeIdentity();

		m_clearClr						= math::Color4(0.0f, 0.0f, 0.0f, 1.0f);
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
		m_pScreenQuad = alloc_object<ScreenQuad>();
		if(m_pScreenQuad->Init(m_pGraphics) == false)
		{
			return false;
		}

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
		m_pGraphics->ClearDepthStencilBuffer(DepthStencilBufferPtr(), 1.0f, 0);


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

		MaterialPtr pMat = m_pScreenQuad->GetMaterial();
		
		pMat->SetProjMatrix(m_projMatrix);
		pMat->SetViewMatrix(m_viewMatrix);
				
		m_pScreenQuad->Render(m_pGraphics, m_pGBuffer);
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
		RenderGBuffer();
		RenderScreenQuad();
		RenderForward();
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
	}

}


namespace engine
{
	bool RenderSystem::ScreenQuad::Init(Sys_GraphicsPtr pGraphics)
	{
		struct Vertex
		{
			math::Vector3			pos;
			math::Vector2			uv;
		};

		Vertex verts[] = 
		{
			{ math::Vector3(-1, 1, 0), math::Vector2(0, 0),},
			{ math::Vector3(1, 1, 0), math::Vector2(1, 0),},
			{ math::Vector3(1, -1, 0), math::Vector2(1, 1),},
			{ math::Vector3(-1, 1, 0), math::Vector2(0, 0),},
			{ math::Vector3(1, -1, 0), math::Vector2(1, 1),},
			{ math::Vector3(-1, -1, 0), math::Vector2(0, 1),},
		};

		m_pVB = pGraphics->CreateBuffer(BT_VERTEX_BUFFER, sizeof(Vertex) * 6, verts, true);
		m_pMaterial = pGraphics->CreateMaterialFromFile("./assets/material/dr_render_screenquad.fx");

		VertexElement vf[] = 
		{
			VertexElement(0, VertexElement::POSITION,G_FORMAT_R32G32B32_FLOAT),
			VertexElement(0, VertexElement::TEXCOORD,G_FORMAT_R32G32_FLOAT),
		};
		VertexFormat format;

		format.SetElement(vf, 2);

		m_pMaterial->SetVertexFormat(format);
		return true;
	}
	void RenderSystem::ScreenQuad::Release()
	{
		if(m_pVB)
		{
			m_pVB->Release();
			m_pVB.reset();
		}
		if(m_pMaterial)
		{
			m_pMaterial->Release();
			m_pMaterial.reset();
		}
	}
	void RenderSystem::ScreenQuad::Render(Sys_GraphicsPtr pGraphics, MultiRenderTargetPtr pGBuffer)
	{
		m_pMaterial->SetGBuffer(pGBuffer);

		pGraphics->SetVertexBuffer(m_pVB, 0, sizeof(math::Vector3) + sizeof(math::Vector2));
		pGraphics->SetPrimitiveType(PT_TRIANGLE_LIST);

		m_pMaterial->ApplyVertexFormat();

		int nPass = 0;

		m_pMaterial->Begin(nPass);

		for(int i = 0; i < nPass; ++i)
		{
			m_pMaterial->ApplyPass(i);
			pGraphics->Draw(6, 0);
		}

		m_pMaterial->End();
	}
	MaterialPtr RenderSystem::ScreenQuad::GetMaterial()
	{
		return m_pMaterial;
	}
}
