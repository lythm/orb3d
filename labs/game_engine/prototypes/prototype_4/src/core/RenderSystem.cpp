#include "core_pch.h"
#include "..\..\include\core\RenderSystem.h"
#include "core\RenderData.h"
#include "core\Sys_Graphics.h"
#include "core\Material.h"
#include "core\g_format.h"

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
		return true;
	}
	void RenderSystem::Release()
	{
		m_renderQueue.clear();
	}

	void RenderSystem::AddRenderData(RenderDataPtr pData)
	{
		m_renderQueue.push_back(pData);
	}
	void RenderSystem::Clear()
	{
		m_renderQueue.clear();
	}
	void RenderSystem::Render()
	{
		m_pGraphics->ClearRenderTarget(RenderTargetPtr(), m_clearClr, m_clearDepth, m_clearStencil, CLEAR_ALL);

		for(size_t i = 0; i < m_renderQueue.size(); ++i)
		{
			SetSemanticsValue(m_renderQueue[i]);


			//m_renderQueue[i]->Render_Depth(m_pGraphics);
			
		}

		for(size_t i = 0; i < m_renderQueue.size(); ++i)
		{
			SetSemanticsValue(m_renderQueue[i]);

			m_renderQueue[i]->Render(m_pGraphics);
		}

		m_pGraphics->Present();
	}

	void RenderSystem::DR_Render()
	{
		m_pGraphics->ClearRenderTarget(RenderTargetPtr(), m_clearClr, m_clearDepth, m_clearStencil, CLEAR_ALL);

		// geometry pass
		for(size_t i = 0; i < m_renderQueue.size(); ++i)
		{
			SetSemanticsValue(m_renderQueue[i]);
			m_renderQueue[i]->DR_Render(m_pGraphics, RenderData::DR_GEOMETRY);
		}
		// lighting pass

		for(size_t i = 0; i < m_renderQueue.size(); ++i)
		{
			SetSemanticsValue(m_renderQueue[i]);
			m_renderQueue[i]->DR_Render(m_pGraphics, RenderData::DR_LIGHTING);
		}

		// posteffect pass

		for(size_t i = 0; i < m_renderQueue.size(); ++i)
		{
			SetSemanticsValue(m_renderQueue[i]);
			m_renderQueue[i]->DR_Render(m_pGraphics, RenderData::DR_POSTEFFECT);
		}
		// merge pass
		for(size_t i = 0; i < m_renderQueue.size(); ++i)
		{
			SetSemanticsValue(m_renderQueue[i]);
			m_renderQueue[i]->DR_Render(m_pGraphics, RenderData::DR_MERGE);
		}
		
		
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

		pMaterial->SetMatrixBySemantic("MATRIX_WORLD", world);
		pMaterial->SetMatrixBySemantic("MATRIX_VIEW", m_viewMatrix);
		pMaterial->SetMatrixBySemantic("MATRIX_PROJ", m_projMatrix);
		pMaterial->SetMatrixBySemantic("MATRIX_WVP", world * m_viewMatrix * m_projMatrix);

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
}
