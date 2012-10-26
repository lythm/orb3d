#include "d11graphics_pch.h"
#include "D3D11Texture3D.h"


namespace engine
{
	D3D11Texture3D::D3D11Texture3D(ID3D11Texture3D* pTex)
	{
		m_pTex = pTex;
	}


	D3D11Texture3D::~D3D11Texture3D(void)
	{
	}
	ID3D11Texture3D* D3D11Texture3D::GetD3D11Resource()
	{
		return m_pTex;
	}
}