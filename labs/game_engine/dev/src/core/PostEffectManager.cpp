#include "core_pch.h"
#include "..\..\include\core\PostEffectManager.h"
#include "core\PostEffect.h"
#include "core\RenderSystem.h"
#include "core\RenderTarget.h"
#include "core\Material.h"
#include "core\VertexFormat.h"

#include "core\PostEffect_SSAO.h"
#include "core_utils.h"

namespace ld3d
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

		int w = pRS->GetFrameBufferWidth();
		int h = pRS->GetFrameBufferHeight();

		if(false == CreateRT(w, h))
		{
			return false;
		}
		
		m_pFinalMaterial = pRS->CreateMaterialFromFile("./assets/standard/material/dr_render_final.fx");
		if(m_pFinalMaterial == nullptr)
		{
			return false;
		}

		VertexElement vf[] = 
		{
			VertexElement(0, VertexElement::POSITION,G_FORMAT_R32G32B32_FLOAT),
		};
		VertexFormat format;

		format.SetElement(vf, 1);

		m_pFinalMaterial->SetVertexFormat(format);


		/*boost::shared_ptr<PostEffect_SSAO> pSSAO = alloc_object<PostEffect_SSAO>();
		pSSAO->Initialize(m_pRS);
		
		m_effects.push_back(pSSAO);*/

		return true;
	}
	void PostEffectManager::Release()
	{
		for(size_t i = 0; i < m_effects.size(); ++i)
		{
			m_effects[i]->Release();
		}

		m_effects.clear();

		if(m_pInput)
		{
			m_pInput->Release();
			m_pInput.reset();
		}
		if(m_pOutput)
		{
			m_pOutput->Release();
			m_pOutput.reset();
		}

		if(m_pFinalMaterial)
		{
			m_pFinalMaterial->Release();
			m_pFinalMaterial.reset();
		}
	}
	void PostEffectManager::Render()
	{
		for(size_t i = 0; i < m_effects.size(); ++i)
		{
			m_effects[i]->Render(m_pRS, m_pInput, m_pOutput);
			SwapRenderTarget();
		}
		SwapRenderTarget();
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
	void PostEffectManager::Resize(int cx, int cy)
	{
		if(cx == 0 || cy == 0)
		{
			return;
		}

		CreateRT(cx, cy);
	}
	bool PostEffectManager::CreateRT(int w, int h)
	{
		if(m_pInput != nullptr)
		{
			m_pInput->Release();
			m_pInput.reset();
		}
		if(m_pOutput != nullptr)
		{
			m_pOutput->Release();
			m_pOutput.reset();
		}

		G_FORMAT formats[1] = {G_FORMAT_R8G8B8A8_UNORM,};
		m_pInput = m_pRS->CreateRenderTarget(1, w, h, formats);

		if(m_pInput == nullptr)
		{
			return false;
		}

		m_pOutput = m_pRS->CreateRenderTarget(1, w, h, formats);

		if(m_pOutput == nullptr)
		{
			return false;
		}

		return true;
	}
	void PostEffectManager::RenderToFrameBuffer()
	{
		m_pRS->SetRenderTarget(RenderTargetPtr());
		m_pRS->ClearRenderTarget(RenderTargetPtr(), 0, m_pRS->GetClearColor());

		m_pFinalMaterial->SetTextureByName("post_output", m_pOutput->AsTexture(0));

		m_pRS->DrawFullScreenQuad(m_pFinalMaterial);
	}
	void PostEffectManager::AddEffect(PostEffectPtr pEffect)
	{
		m_effects.push_back(pEffect);
	}
}
