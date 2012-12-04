#include "d11graphics_pch.h"
#include "D3D11RenderTarget.h"
#include "D3D11Texture.h"
#include "D3D11DepthStencilBuffer.h"
#include "D3D11Format.h"

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
	bool D3D11RenderTarget::Create(int w, int h, G_FORMAT format, int miplvls)
	{

		if(m_pRenderTargetView)
		{
			m_pRenderTargetView->Release();
			m_pRenderTargetView = NULL;
		}

		D3D11_TEXTURE2D_DESC td;
		ZeroMemory(&td, sizeof(td));

		td.ArraySize = 1;
		td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		td.CPUAccessFlags = 0;
		td.Format = D3D11Format::Convert(format);
		td.Height = h;
		td.MipLevels = miplvls;
		td.MiscFlags = 0;
		td.SampleDesc.Count = 1;
		td.SampleDesc.Quality = 0;
		td.Usage = D3D11_USAGE_DEFAULT;
		td.Width = w;

		ID3D11Texture2D* pD3D11Tex = NULL;
		if(FAILED(m_pDevice->CreateTexture2D(&td, NULL, &pD3D11Tex)))
		{
			return false;
		}

		D3D11Texture* pTex = new D3D11Texture(m_pContext);

		if(false == pTex->CreateFromRes(pD3D11Tex))
		{
			pD3D11Tex->Release();
			return false;
		}

		if(pTex == NULL)
		{
			return false;
		}
		m_pTex = TexturePtr(pTex);
		
		if(FAILED(m_pDevice->CreateRenderTargetView( pD3D11Tex, NULL, &m_pRenderTargetView)))
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
		
		m_pDevice->Release();

		m_pDepthBuffer.reset();
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

	DepthStencilBufferPtr D3D11RenderTarget::GetDepthStencilBuffer()
	{
		return m_pDepthBuffer;
	}
	void D3D11RenderTarget::SetDepthStencilBuffer(DepthStencilBufferPtr pBuffer)
	{
		m_pDepthBuffer = pBuffer;
	}
}
