#include "d11graphics_pch.h"
#include "D3D11RenderTarget.h"
#include "D3D11Texture.h"
#include "D3D11DepthStencilBuffer.h"

namespace engine
{
	D3D11RenderTarget::D3D11RenderTarget(ID3D11DeviceContext* pContext)
	{
		m_pContext					= pContext;

		m_pDevice					= NULL;

		m_pContext->GetDevice(&m_pDevice);
		m_pRenderTargetView			= NULL;
	}


	D3D11RenderTarget::~D3D11RenderTarget(void)
	{
	}
	bool D3D11RenderTarget::Create(TexturePtr pTex)
	{
		if(m_pRenderTargetView)
		{
			m_pRenderTargetView->Release();
			m_pRenderTargetView = NULL;
		}
		if(pTex == NULL)
		{
			return false;
		}
		m_pTex = pTex;
		if(FAILED(m_pDevice->CreateRenderTargetView( ((D3D11Texture*)pTex.get())->GetD3D11Resource(), NULL, &m_pRenderTargetView)))
		{
			return false;
		}

		return true;
	}
	void D3D11RenderTarget::Release()
	{
		if(m_pTex)
		{
			m_pTex->Release();
			m_pTex.reset();
		}
		if(m_pRenderTargetView)
		{
			m_pRenderTargetView->Release();
			m_pRenderTargetView = NULL;
		}
		if(m_pDepthBuffer)
		{
			m_pDepthBuffer->Release();
			m_pDepthBuffer.reset();
		}
		m_pDevice->Release();
		m_pContext = NULL;
	}
	
	ID3D11RenderTargetView*	D3D11RenderTarget::GetD3D11RenderTargetView()
	{
		return m_pRenderTargetView;
	}
	ID3D11DepthStencilView*	D3D11RenderTarget::GetD3D11DepthStencilView()
	{
		if(m_pDepthBuffer == nullptr)
		{
			return nullptr;
		}
		return ((D3D11DepthStencilBuffer*)m_pDepthBuffer.get())->GetD3D11DepthStencilView();
	}
	TexturePtr D3D11RenderTarget::AsTexture()
	{
		return m_pTex;
	}
	void D3D11RenderTarget::Clear(const math::Color4& clr, float d, int s)
	{
		m_pContext->ClearRenderTargetView(m_pRenderTargetView, clr.v);
		if(m_pDepthBuffer)
		{
			m_pDepthBuffer->Clear(d, s);
		}
	}
	DepthStencilBufferPtr D3D11RenderTarget::GetDepthStencilBuffer()
	{
		return m_pDepthBuffer;
	}
	void D3D11RenderTarget::AttachDepthStencilBuffer(DepthStencilBufferPtr pBuffer)
	{
		m_pDepthBuffer = pBuffer;
	}
}
