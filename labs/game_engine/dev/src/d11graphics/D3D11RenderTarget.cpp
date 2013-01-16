#include "d11graphics_pch.h"
#include "D3D11RenderTarget.h"
#include "D3D11DepthStencilBuffer.h"

#include "D3D11Texture.h"
#include "D3D11Format.h"


namespace ld3d
{
	D3D11RenderTarget::D3D11RenderTarget(ID3D11DeviceContext* pContext)
	{
		m_pContext					= pContext;
		m_pRTViews					= NULL;
		m_pDevice					= NULL;
		m_pContext->GetDevice(&m_pDevice);

		m_width						= 0;
		m_height					= 0;

	}


	D3D11RenderTarget::~D3D11RenderTarget(void)
	{
	}

	int D3D11RenderTarget::GetRenderTargetCount()
	{
		return (int)m_pTexures.size();
	}
	TexturePtr D3D11RenderTarget::AsTexture(int index)
	{
		return m_pTexures[index];
	}
	void D3D11RenderTarget::SetDepthStencilBuffer(DepthStencilBufferPtr pDepthBuffer)
	{
		m_pDepthBuffer = pDepthBuffer;
	}
	DepthStencilBufferPtr D3D11RenderTarget::GetDepthStencilBuffer()
	{
		return m_pDepthBuffer;
	}
	void D3D11RenderTarget::Release()
	{
		for(size_t i = 0; i < m_pTexures.size(); ++i)
		{
			m_pTexures[i]->Release();
			m_pRTViews[i]->Release();
			
		}
		
		delete [] m_pRTViews;
		m_pRTViews = NULL;
		m_pTexures.clear();
		m_pDevice->Release();
		m_pContext = NULL;
		m_pDepthBuffer.reset();
	}
	bool D3D11RenderTarget::Create(int count, int w, int h, G_FORMAT formats[], int miplvls)
	{
		if(count == 0)
		{
			return false;
		}

		if(w == 0 || h == 0)
		{
			return false;
		}

		m_width = w;
		m_height = h;

		m_pRTViews = new ID3D11RenderTargetView*[count];

		for(int i = 0; i < count; ++i)
		{
			D3D11_TEXTURE2D_DESC td;
			ZeroMemory(&td, sizeof(td));

			td.ArraySize = 1;
			td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			td.CPUAccessFlags = 0;
			td.Format = D3D11Format::Convert(formats[i]);
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

			m_pTexures.push_back(TexturePtr(pTex));

			if(FAILED(m_pDevice->CreateRenderTargetView( pD3D11Tex, NULL, &m_pRTViews[i])))
			{
				return false;
			}
		}
		return true;
	}

	ID3D11DepthStencilView* D3D11RenderTarget::GetD3D11DepthStencilView()
	{
		if(m_pDepthBuffer == nullptr)
		{
			return NULL;
		}
		return ((D3D11DepthStencilBuffer*)m_pDepthBuffer.get())->GetD3D11DepthStencilView();
	}
	ID3D11RenderTargetView** D3D11RenderTarget::GetD3D11RenderTargetViews()
	{
		return m_pRTViews;
	}
	ID3D11RenderTargetView* D3D11RenderTarget::GetD3D11RenderTargetView(int index)
	{
		return m_pRTViews[index];
	}
	int D3D11RenderTarget::GetWidth(int index)
	{
		return m_width;
	}
	int	D3D11RenderTarget::GetHeight(int index)
	{
		return m_height;
	}
	
}
