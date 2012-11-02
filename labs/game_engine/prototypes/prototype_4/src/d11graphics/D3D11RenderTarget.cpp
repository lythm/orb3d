#include "d11graphics_pch.h"
#include "D3D11RenderTarget.h"
#include "D3D11Texture.h"

namespace engine
{
	D3D11RenderTarget::D3D11RenderTarget(ID3D11DeviceContext* pContext)
	{
		m_pContext					= pContext;

		m_pDevice					= NULL;

		m_pContext->GetDevice(&m_pDevice);
		m_pRenderTargetView			= NULL;
		m_pDepthStencilView			= NULL;
	}


	D3D11RenderTarget::~D3D11RenderTarget(void)
	{
	}
	void D3D11RenderTarget::SetColorBuffer(TexturePtr pTex)
	{
		if(m_pRenderTargetView)
		{
			m_pRenderTargetView->Release();
			m_pRenderTargetView = NULL;
		}
		if(pTex == NULL)
		{
			return;
		}

		if(FAILED(m_pDevice->CreateRenderTargetView( ((D3D11Texture*)pTex.get())->GetD3D11Resource(), NULL, &m_pRenderTargetView)))
		{
			return;
		}

		return;
	}
	
	
	ID3D11RenderTargetView*	D3D11RenderTarget::GetRenderTargetView()
	{
		return m_pRenderTargetView;
	}
}
