#include "core_pch.h"
#include "..\..\include\core\RenderSystem.h"
#include "core\RenderData.h"
#include "core\Sys_Graphics.h"

namespace engine
{
	RenderSystem::RenderSystem(void)
	{
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
			m_renderQueue[i]->Render(m_pGraphics);
		}

		m_pGraphics->Present();
	}
}
