#include "core_pch.h"
#include "..\..\include\core\Mesh.h"
#include "core\Material.h"
#include "core_utils.h"

namespace ld3d
{
	Mesh::Mesh(void)
	{
		m_pIndexData				= NULL;
		m_pVertexData				= NULL;

		m_indexDataBytes			= 0;
		m_vertexDataBytes			= 0;

	}


	Mesh::~Mesh(void)
	{
	}
	void Mesh::Update()
	{

	}
	void* Mesh::GetIndexData()
	{
		return m_pIndexData;
	}
	void* Mesh::GetVertexData()
	{
		return m_pVertexData;
	}
	MaterialPtr Mesh::GetMaterialByIndex(int index)
	{
		return m_materialList[index];
	}
	int	Mesh::GetMaterialCount()
	{
		return (int)m_materialList.size();
	}
	bool Mesh::Create(int indexBufferSize, void* pIndexBuffer, int vertexBufferSize, void* pVertexBuffer, const std::vector<MaterialPtr>& materialList)
	{
		if(pIndexBuffer != nullptr)
		{
			m_pIndexData = mem_alloc(indexBufferSize);
			memcpy(m_pIndexData, pIndexBuffer, indexBufferSize);
			m_indexDataBytes = indexBufferSize;
		}
		else
		{
			m_indexDataBytes = 0;
		}

		m_pVertexData = mem_alloc(vertexBufferSize);
		memcpy(m_pVertexData, pVertexBuffer, vertexBufferSize);
		m_vertexDataBytes = vertexBufferSize;

		m_materialList = materialList;

		return true;
	}
	void Mesh::Destroy()
	{
		mem_free(m_pIndexData);
		m_indexDataBytes = 0;
		mem_free(m_pVertexData);
		m_vertexDataBytes = 0;
		
		for(size_t i = 0; i < m_materialList.size(); ++i)
		{
			m_materialList[i]->Release();
		}
		m_materialList.clear();
		m_submeshList.clear();
	}
	int	Mesh::GetIndexDataBytes()
	{
		return m_indexDataBytes;
	}
	int Mesh::GetVertexDataBytes()
	{
		return m_vertexDataBytes;
	}
	void Mesh::AddSubMesh(SubMeshPtr pSub)
	{
		m_submeshList.push_back(pSub);
	}
	int	Mesh::GetSubMeshCount()
	{
		return (int)m_submeshList.size();
	}
	SubMeshPtr Mesh::GetSubMesh(int index)
	{
		return m_submeshList[index];
	}
}
