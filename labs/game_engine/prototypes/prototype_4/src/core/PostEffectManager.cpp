#include "core_pch.h"
#include "..\..\include\core\PostEffectManager.h"
#include "core\PostEffect.h"

namespace engine
{
	PostEffectManager::PostEffectManager(void)
	{
	}


	PostEffectManager::~PostEffectManager(void)
	{
	}
	bool PostEffectManager::Initialize(RenderSystemPtr pRS)
	{
		m_pRS = pRS;

		
		return true;
	}
	void PostEffectManager::Release()
	{
		for(size_t i = 0; i < m_effects.size(); ++i)
		{
			m_effects[i]->Release();
		}

		m_effects.clear();

	}
	void PostEffectManager::Render()
	{
		for(size_t i = 0; i < m_effects.size(); ++i)
		{
			m_effects[i]->Render(m_pRS, m_pInput, m_pOutput);
			SwapRenderTarget();
		}
	}
	void PostEffectManager::SwapRenderTarget()
	{
		RenderTargetPtr pTmp;
		pTmp = m_pInput;
		m_pInput = m_pOutput;
		m_pOutput = pTmp;
	}
	RenderTargetPtr PostEffectManager::GetInput()
	{
		return m_pInput;
	}
	RenderTargetPtr PostEffectManager::GetOutput()
	{
		return m_pOutput;
	}
	int	PostEffectManager::GetEffectCount()
	{
		return (int)m_effects.size();
	}
}
