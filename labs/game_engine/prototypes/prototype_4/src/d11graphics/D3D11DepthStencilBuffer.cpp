#include "d11graphics_pch.h"
#include "D3D11DepthStencilBuffer.h"
#include "D3D11Texture.h"


namespace engine
{
	D3D11DepthStencilBuffer::D3D11DepthStencilBuffer(ID3D11DeviceContext* pContext)
	{

		m_pContext					= pContext;

		m_pDevice					= NULL;

		m_pContext->GetDevice(&m_pDevice);
		m_pDepthStencilView			= NULL;

	}


	D3D11DepthStencilBuffer::~D3D11DepthStencilBuffer(void)
	{
	}

	bool D3D11DepthStencilBuffer::Create(TexturePtr pTex)
	{
		if(m_pTex)
		{
			m_pTex->Release();
			m_pTex.reset();
		}
		if(m_pDepthStencilView)
		{
			m_pDepthStencilView->Release();
			m_pDepthStencilView = NULL;
		}
		if(pTex == NULL)
		{
			return false;
		}
		m_pTex = pTex;

		D3D11_DEPTH_STENCIL_VIEW_DESC d;
		ZeroMemory(&d, sizeof(d));

		d.Format = DXGI_FORMAT_D32_FLOAT;
		d.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		d.Flags = 0;
		d.Texture2D.MipSlice = 0;

		if(FAILED(m_pDevice->CreateDepthStencilView( ((D3D11Texture*)pTex.get())->GetD3D11Resource(), &d, &m_pDepthStencilView)))
		{
			return false;
		}

		return true;
	}
	void D3D11DepthStencilBuffer::Release()
	{
		if(m_pTex)
		{
			m_pTex->Release();
			m_pTex.reset();

		}
		if(m_pDepthStencilView)
		{
			m_pDepthStencilView->Release();
			m_pDepthStencilView = NULL;
		}

		m_pDevice->Release();
		m_pContext = NULL;
	}
	
	ID3D11DepthStencilView*	D3D11DepthStencilBuffer::GetD3D11DepthStencilView()
	{
		return m_pDepthStencilView;
	}
	TexturePtr D3D11DepthStencilBuffer::AsTexture()
	{
		return m_pTex;
	}
	void D3D11DepthStencilBuffer::Clear(float depth, int stencil)
	{
		m_pContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL , depth, stencil);
	}

}
