#include "graphics_pch.h"
#include "D3D11GeometryBuffer.h"
#include "D3D11TypeMapping.h"

namespace engine
{
	D3D11GeometryBuffer::D3D11GeometryBuffer(ID3D11DeviceContext* pContext)
	{
		m_pContext = pContext;
	}


	D3D11GeometryBuffer::~D3D11GeometryBuffer(void)
	{
	}

	void* D3D11GeometryBuffer::MapVertexBuffer(MAP_HINT hint)
	{
		return MapBuffer(m_pVertexBuffer, hint);
	}
	void D3D11GeometryBuffer::UnmapVertexBuffer()
	{
		UnmapBuffer(m_pVertexBuffer);
	}

	void* D3D11GeometryBuffer::MapIndexBuffer(MAP_HINT hint)
	{
		return MapBuffer(m_pIndexBuffer, hint);
	}
	void D3D11GeometryBuffer::UnmapIndexBuffer()
	{
		UnmapBuffer(m_pIndexBuffer);
	}
	void* D3D11GeometryBuffer::MapBuffer(ID3D11Buffer* pBuffer, MAP_HINT hint)
	{

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

		if(FAILED(m_pContext->Map(pBuffer, 0, map, 0, &desc)))
		{
			return NULL;
		}

		return desc.pData;
	}
	void D3D11GeometryBuffer::UnmapBuffer(ID3D11Buffer* pBuffer)
	{
		m_pContext->Unmap(pBuffer, 0);
	}

	bool D3D11GeometryBuffer::AllocVertexBuffer(unsigned int bytes, bool dynamic)
	{
		D3D11_BUFFER_DESC desc;

		desc.BindFlags =  D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = bytes;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		desc.Usage = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;

		ID3D11Device* pDevice = NULL;
		m_pContext->GetDevice(&pDevice);

		HRESULT ret = pDevice->CreateBuffer(&desc, NULL, &m_pVertexBuffer);
		if(FAILED(ret))
		{
			pDevice->Release();
			return false;
		}

		pDevice->Release();
		return true;

	}
	void D3D11GeometryBuffer::FreeVertexBuffer()
	{
		if(m_pVertexBuffer != NULL)
		{
			m_pVertexBuffer->Release();
			m_pVertexBuffer = NULL;
		}
	}
	bool D3D11GeometryBuffer::AllocIndexBuffer(unsigned int bytes, bool dynamic)
	{

		// Fill in a buffer description.
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.Usage           = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth       = bytes;
		bufferDesc.BindFlags       = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags  = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags       = 0;
		bufferDesc.StructureByteStride = 0;

		ID3D11Device* pDevice = NULL;
		m_pContext->GetDevice(&pDevice);

		if(FAILED(pDevice->CreateBuffer(&bufferDesc, NULL, &m_pIndexBuffer)))
		{
			pDevice->Release();
			return false;
		}
		pDevice->Release();

		return true;

	}
	void D3D11GeometryBuffer::FreeIndexBuffer()
	{
		
		if(m_pIndexBuffer != NULL)
		{
			m_pIndexBuffer->Release();
			m_pIndexBuffer = NULL;
		}
	}
	ID3D11Buffer* D3D11GeometryBuffer::GetD3DVertexBuffer()
	{
		return m_pVertexBuffer;
	}
	ID3D11Buffer* D3D11GeometryBuffer::GetD3DIndexBuffer()
	{
		return m_pIndexBuffer;
	}
	void D3D11GeometryBuffer::Apply(uint32 vertexBufferoffset, uint32 vertexBufferstride, uint32 indexBufferOffset)
	{
		m_pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, indexBufferOffset);
		m_pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &vertexBufferstride, &vertexBufferoffset);
	}
	void D3D11GeometryBuffer::Apply(uint32 vertexStride)
	{
		Apply(0, vertexStride, 0);
	}

}
