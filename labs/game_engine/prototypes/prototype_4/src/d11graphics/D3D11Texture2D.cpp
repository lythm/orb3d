#include "d11graphics_pch.h"
#include "D3D11Texture2D.h"


namespace engine
{
	D3D11Texture2D::D3D11Texture2D(void)
	{
		m_pTex = NULL;
	}


	D3D11Texture2D::~D3D11Texture2D(void)
	{
	}
	ID3D11Texture2D* D3D11Texture2D::GetD3D11Resource()
	{
		return m_pTex;
	}
}