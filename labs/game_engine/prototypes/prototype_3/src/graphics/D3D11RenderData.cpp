#include "graphics_pch.h"
#include "D3D11RenderData.h"
#include "GFXShader.h"

namespace engine
{
	D3D11RenderData::D3D11RenderData(ID3D11DeviceContext* pContext)
	{
		m_pContext = pContext;

		m_pVertexBuffer			= NULL;
		m_pIndexBuffer			= NULL;
	}


	D3D11RenderData::~D3D11RenderData(void)
	{
	}
	void D3D11RenderData::Release()
	{
		if(m_pVertexBuffer)
		{
			m_pVertexBuffer->Release();
			m_pVertexBuffer = NULL;
		}

		if(m_pIndexBuffer)
		{
			m_pIndexBuffer->Release();
			m_pIndexBuffer = NULL;
		}

		if(m_pShader != NULL)
		{
			m_pShader->Release();
			m_pShader.reset();
		}
		m_pContext = NULL;
	}

	bool D3D11RenderData::AllocIndexBuffer(unsigned int bytes, void* pInitData, bool dynamic)
	{

		// Fill in a buffer description.
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.Usage           = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth       = bytes;
		bufferDesc.BindFlags       = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags  = dynamic ? D3D11_CPU_ACCESS_WRITE : 0;
		bufferDesc.MiscFlags       = 0;
		bufferDesc.StructureByteStride = 0;

		ID3D11Device* pDevice = NULL;
		m_pContext->GetDevice(&pDevice);

		D3D11_SUBRESOURCE_DATA InitData = {pInitData, 0, 0,};

		if(FAILED(pDevice->CreateBuffer(&bufferDesc, pInitData == NULL ? NULL :&InitData, &m_pIndexBuffer)))
		{
			pDevice->Release();
			return false;
		}
		pDevice->Release();

		return true;

	}
	bool D3D11RenderData::AllocVertexBuffer(unsigned int bytes, void* pInitData, bool dynamic)
	{
		D3D11_BUFFER_DESC desc;

		desc.BindFlags =  D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = bytes;
		desc.CPUAccessFlags = dynamic ? D3D11_CPU_ACCESS_WRITE : 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		desc.Usage = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;

		ID3D11Device* pDevice = NULL;
		m_pContext->GetDevice(&pDevice);


		D3D11_SUBRESOURCE_DATA InitData = {pInitData, 0, 0,};
		
		HRESULT ret = pDevice->CreateBuffer(&desc, pInitData == NULL ? NULL : &InitData, &m_pVertexBuffer);
		if(FAILED(ret))
		{
			pDevice->Release();
			return false;
		}

		pDevice->Release();
		return true;

	}
	void* D3D11RenderData::MapVertexBuffer(MAP_HINT hint)
	{
		return MapBuffer(m_pVertexBuffer, hint);
	}
	void D3D11RenderData::UnmapVertexBuffer()
	{
		UnmapBuffer(m_pVertexBuffer);
	}

	void* D3D11RenderData::MapIndexBuffer(MAP_HINT hint)
	{
		return MapBuffer(m_pIndexBuffer, hint);
	}
	void D3D11RenderData::UnmapIndexBuffer()
	{
		UnmapBuffer(m_pIndexBuffer);
	}
	void* D3D11RenderData::MapBuffer(ID3D11Buffer* pBuffer, MAP_HINT hint)
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
	void D3D11RenderData::UnmapBuffer(ID3D11Buffer* pBuffer)
	{
		m_pContext->Unmap(pBuffer, 0);
	}
	void D3D11RenderData::SetTransform(const math::Matrix44& transform)
	{
		m_worldTransform = transform;
	}


	ID3D11Buffer* D3D11RenderData::GetD3DVertexBuffer()
	{
		return m_pVertexBuffer;
	}
	ID3D11Buffer* D3D11RenderData::GetD3DIndexBuffer()
	{
		return m_pIndexBuffer;
	}
	void D3D11RenderData::SetShader(ShaderPtr pShader)
	{
		m_pShader = pShader;
	}
}