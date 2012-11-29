#include "core_pch.h"
#include "..\..\include\core\RenderSystem.h"
#include "core\RenderData.h"
#include "core\Sys_Graphics.h"
#include "core\GFX.h"

namespace engine
{
	RenderSystem::RenderSystem(void)
	{
		m_viewMatrix.MakeIdentity();
		m_projMatrix.MakeIdentity();
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
		m_pGraphics->ClearFrameBuffer();

		for(size_t i = 0; i < m_renderQueue.size(); ++i)
		{
			SetSemanticsValue(m_renderQueue[i]);
			m_renderQueue[i]->Render(m_pGraphics);
		}

		m_pGraphics->Present();
	}

	void RenderSystem::DR_Render()
	{
		m_pGraphics->ClearFrameBuffer();

		for(size_t i = 0; i < m_renderQueue.size(); ++i)
		{
			SetSemanticsValue(m_renderQueue[i]);
			m_renderQueue[i]->DR_RenderDepth();
		}
		for(size_t i = 0; i < m_renderQueue.size(); ++i)
		{
			SetSemanticsValue(m_renderQueue[i]);
			m_renderQueue[i]->DR_Render();
		}
		for(size_t i = 0; i < m_renderQueue.size(); ++i)
		{
			SetSemanticsValue(m_renderQueue[i]);
			m_renderQueue[i]->DR_PostEffect();
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
		GFXPtr pGFX = pData->GetGFX();

		math::Matrix44 world = pData->GetWorldMatrix();

		pGFX->SetMatrixBySemantic("MATRIX_WORLD", world);
		pGFX->SetMatrixBySemantic("MATRIX_VIEW", m_viewMatrix);
		pGFX->SetMatrixBySemantic("MATRIX_PROJ", m_projMatrix);
		pGFX->SetMatrixBySemantic("MATRIX_WVP", world * m_viewMatrix * m_projMatrix);

	}
	Sys_GraphicsPtr	RenderSystem::GetSysGraphics()
	{
		return m_pGraphics;
	}
}
