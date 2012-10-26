#include "d11graphics_pch.h"
#include "D3D11Texture1D.h"

namespace engine
{
	D3D11Texture1D::D3D11Texture1D(ID3D11Texture1D* pTex)
	{
		m_pTex = pTex;
	}


	D3D11Texture1D::~D3D11Texture1D(void)
	{
	}
	ID3D11Texture1D* D3D11Texture1D::GetD3D11Resource()
	{
		return m_pTex;
	}

}