#include "graphics_pch.h"
#include "D3D11Texture2D.h"

namespace engine
{
	D3D11Texture2D::D3D11Texture2D(ID3D11Resource* pTex)
	{
		m_pTexture				= pTex;

		m_pRenderTargetView		= NULL;
	}


	D3D11Texture2D::~D3D11Texture2D(void)
	{
	}
	void D3D11Texture2D::Release()
	{
		if(m_pTexture)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
	}
	ID3D11Resource* D3D11Texture2D::GetD3D11Resource()
	{
		return m_pTexture;
	}

	ID3D11RenderTargetView* D3D11Texture2D::GetD3D11RenderTargetView()
	{
		return m_pRenderTargetView;
	}
}
