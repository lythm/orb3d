#include "core_pch.h"
#include "..\..\include\core\SubMesh.h"
#include "core\Mesh.h"


namespace ld3d
{
	SubMesh::SubMesh()
	{
		
	}


	SubMesh::~SubMesh(void)
	{
	}
	void SubMesh::Create(MeshPtr pMesh, int indexOffset, int indexCount, int vertexOffset, int vertexCount, int vertexStride, int matIndex, int primCount, PRIMITIVE_TYPE primType, const VertexFormat& vf, G_FORMAT indexFormat)
	{
		m_pMesh						= pMesh;

		m_indexOffset				= indexOffset;
		m_vertexOffset				= vertexOffset;

		m_vertexCount				= vertexCount;
		m_indexCount				= indexCount;
		m_primitiveCount			= primCount;
		m_materialIndex				= matIndex;
		m_vertexStride				= vertexStride;

		m_indexed					= pMesh->GetIndexData() == NULL ? false : true;
		m_primitiveType				= primType;

		m_vertexFormat				= vf;
		m_indexFormat				= indexFormat;
	}
	G_FORMAT SubMesh::GetIndexFormat()
	{
		return m_indexFormat;
	}
	const VertexFormat& SubMesh::GetVertexFormat()
	{
		return m_vertexFormat;
	}
	void* SubMesh::GetIndexData()
	{
		return m_pMesh->GetIndexData();
	}
	void* SubMesh::GetVertexData()
	{
		return m_pMesh->GetVertexData();
	}
	int SubMesh::GetIndexDataOffset()
	{
		return m_indexOffset;
	}
	int SubMesh::GetVertexDataOffset()
	{
		return m_vertexOffset;
	}
	int	SubMesh::GetIndexDataBytes()
	{
		return m_indexCount * sizeof(uint16);
	}
	int SubMesh::GetVertexDataBytes()
	{
		return m_vertexCount * m_vertexStride;
	}
	int SubMesh::GetIndexCount()
	{
		return m_indexCount;
	}
	int	SubMesh::GetVertexCount()
	{
		return m_vertexCount;
	}
	int	SubMesh::GetVertexStride()
	{
		return m_vertexStride;
	}

	MaterialPtr SubMesh::GetMaterial()
	{
		return m_pMesh->GetMaterialByIndex(m_materialIndex);
	}
	int SubMesh::GetPrimitiveCount()
	{
		return m_primitiveCount;
	}
	PRIMITIVE_TYPE SubMesh::GetPrimitiveType()
	{
		return m_primitiveType;
	}
	bool SubMesh::IsIndexed()
	{
		return m_indexed;
	}
}
