#include "d11graphics_pch.h"
#include "D3D11Texture.h"
#include "D3D11Format.h"

namespace ld3d
{
	D3D11Texture::D3D11Texture(ID3D11DeviceContext* pContext)
	{
		m_pContext = pContext;
		m_pTex = NULL;

		m_pContext->GetDevice(&m_pDevice);

		m_type = TEX_UNKNOWN;

		m_pShaderView = NULL;

	}


	D3D11Texture::~D3D11Texture(void)
	{
	}
	ID3D11Resource* D3D11Texture::GetD3D11Resource()
	{
		return m_pTex;
	}
	void D3D11Texture::Release()
	{
		if(m_pTex)
		{
			m_pTex->Release();
			m_pTex = NULL;
		}
		if(m_pShaderView)
		{
			m_pShaderView->Release();
			m_pShaderView = NULL;
		}
		if(m_pDevice)
		{
			m_pDevice->Release();
			m_pDevice = NULL;
		}
		m_pContext = NULL;
	}
	TEXTURE_TYPE D3D11Texture::GetType()
	{
		return m_type;
	}

	bool D3D11Texture::LoadFromFile(const char* szFile)
	{
		HRESULT ret = D3DX11CreateTextureFromFileA(m_pDevice, szFile, NULL, NULL, &m_pTex, NULL);

		if(FAILED(ret))
		{
			return false;
		}
		
		D3D11_RESOURCE_DIMENSION dim;
		m_pTex->GetType(&dim);
		
		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
		ZeroMemory(&desc, sizeof(desc));


		switch(dim)
		{
		case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
			m_type = TEX_1D;
			break;
		case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
			{
				m_type = TEX_2D;
				D3D11_TEXTURE2D_DESC td;
				((ID3D11Texture2D*)m_pTex)->GetDesc(&td);

				desc.Format = td.Format;

				desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				desc.Texture2D.MipLevels = td.MipLevels;
				desc.Texture2D.MostDetailedMip = 0;

			}
			break;
		case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
			m_type = TEX_3D;
			break;
		default:
			return false;
		}

		if(FAILED(m_pDevice->CreateShaderResourceView(m_pTex, &desc, &m_pShaderView)))
		{
			m_pTex->Release();
			m_pTex = NULL;
			return false;
		}


		return true;
	}
	ID3D11ShaderResourceView* D3D11Texture::GetShaderResourceView()
	{
		return m_pShaderView;
	}
	bool D3D11Texture::CreateFromRes(ID3D11Resource* pRes, G_FORMAT view_format)
	{
		m_pTex = pRes;
		
		D3D11_RESOURCE_DIMENSION dim;
		m_pTex->GetType(&dim);
		
		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
		ZeroMemory(&desc, sizeof(desc));

		switch(dim)
		{
		case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
			m_type = TEX_1D;
			break;
		case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
			{
				m_type = TEX_2D;
				D3D11_TEXTURE2D_DESC td;
				((ID3D11Texture2D*)m_pTex)->GetDesc(&td);

				if(view_format == G_FORMAT_UNKNOWN)
				{
					desc.Format = td.Format;
				}
				else
				{
					desc.Format = D3D11Format::Convert(view_format);
				}

				desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				desc.Texture2D.MipLevels = td.MipLevels;
				desc.Texture2D.MostDetailedMip = 0;

			}
			break;
		case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
			m_type = TEX_3D;
			break;
		default:
			return false;
		}

		if(FAILED(m_pDevice->CreateShaderResourceView(m_pTex, &desc, &m_pShaderView)))
		{
			m_pTex->Release();
			m_pTex = NULL;
			return false;
		}

		return true;
	}

}
