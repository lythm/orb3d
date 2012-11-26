#include "core_pch.h"
#include "..\..\include\core\Mesh.h"


namespace engine
{
	Mesh::Mesh(void)
	{
		m_pIndexData				= NULL;
		m_pVertexData				= NULL;

	}


	Mesh::~Mesh(void)
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
	GFXPtr Mesh::GetMaterialByIndex(int index)
	{
		return m_materialList[index];
	}
	int	Mesh::GetMaterialCount()
	{
		return (int)m_materialList.size();
	}
	bool Mesh::Create(int indexBufferSize, int vertexBufferSize, const std::vector<GFXPtr>& materialList)
	{

		return true;
	}
}
