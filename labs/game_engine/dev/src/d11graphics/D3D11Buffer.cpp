#include "d11graphics_pch.h"
#include "D3D11Buffer.h"


namespace ld3d
{
	D3D11Buffer::D3D11Buffer(ID3D11Buffer* pBuffer, ID3D11DeviceContext* pContext)
	{
		m_pBuffer = pBuffer;
		m_pContext = pContext;
	}


	D3D11Buffer::~D3D11Buffer(void)
	{
	}
	ID3D11Buffer* D3D11Buffer::GetD3D11BufferInterface()
	{
		return m_pBuffer;
	}
	void D3D11Buffer::Release()
	{
		if(m_pBuffer)
		{
			m_pBuffer->Release();
			m_pBuffer = NULL;
		}

		m_pContext = NULL;
	}

	void* D3D11Buffer::Map(MAP_HINT hint)
	{

		if(m_pBuffer == NULL)
		{
			return NULL;
		}

		D3D11_MAPPED_SUBRESOURCE desc;

		D3D11_MAP map = D3D11_MAP_WRITE;

		switch(hint)
		{
		case MAP_DISCARD:
			map = D3D11_MAP_WRITE_DISCARD;
			break;
		case MAP_NO_OVERWRITE:
			map = D3D11_MAP_WRITE_NO_OVERWRITE;
			break;
		case MAP_DEFAULT:
			map = D3D11_MAP_WRITE;
			break;
		default:
			break;
		}

		if(FAILED(m_pContext->Map(m_pBuffer, 0, map, 0, &desc)))
		{
			return NULL;
		}

		return desc.pData;
	}
	void D3D11Buffer::Unmap()
	{
		m_pContext->Unmap(m_pBuffer, 0);
	}
}