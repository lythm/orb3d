#include "d11graphics_pch.h"
#include "D3D11DepthStencilBuffer.h"
#include "D3D11Texture.h"
#include "D3D11Format.h"


namespace ld3d
{
	D3D11DepthStencilBuffer::D3D11DepthStencilBuffer(ID3D11DeviceContext* pContext)
	{

		m_pContext					= pContext;
		m_pBuffer					= nullptr;
		m_pDepthStencilView			= NULL;
	}


	D3D11DepthStencilBuffer::~D3D11DepthStencilBuffer(void)
	{
	}

	bool D3D11DepthStencilBuffer::Create(int w, int h, G_FORMAT format)
	{

		D3D11_TEXTURE2D_DESC td;
		ZeroMemory(&td, sizeof(td));

		td.ArraySize = 1;
		td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		
		td.CPUAccessFlags = 0;
		td.Format = D3D11Format::Convert(format);
		td.Width = w;
		td.Height = h;
		td.MipLevels = 1;
		td.ArraySize = 1;
		td.MiscFlags = 0;
		td.SampleDesc.Count = 1;
		td.SampleDesc.Quality = 0;
		td.Usage = D3D11_USAGE_DEFAULT;
				
		ID3D11Device* pDevice = NULL;

		m_pContext->GetDevice(&pDevice);

		if(FAILED(pDevice->CreateTexture2D(&td, NULL, &m_pBuffer)))
		{
			pDevice->Release();
			return DepthStencilBufferPtr();
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC d;
		ZeroMemory(&d, sizeof(d));

		d.Format = D3D11Format::Convert(format);
		d.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		d.Flags = 0;
		d.Texture2D.MipSlice = 0;

		if(FAILED(pDevice->CreateDepthStencilView( m_pBuffer, &d, &m_pDepthStencilView)))
		{
			pDevice->Release();
			return false;
		}

		pDevice->Release();

		return true;
	}
	void D3D11DepthStencilBuffer::Release()
	{
		if(m_pBuffer)
		{
			m_pBuffer->Release();
			m_pBuffer = NULL;
		}

		if(m_pDepthStencilView)
		{
			m_pDepthStencilView->Release();
			m_pDepthStencilView = NULL;
		}
		
		m_pContext = NULL;
	}
	
	ID3D11DepthStencilView*	D3D11DepthStencilBuffer::GetD3D11DepthStencilView()
	{
		return m_pDepthStencilView;
	}
	
}
