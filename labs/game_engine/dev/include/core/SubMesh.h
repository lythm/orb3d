#pragma once

#include "core\VertexFormat.h"

namespace ld3d
{
	class EXPORT_CLASS SubMesh
	{
	public:
		SubMesh();
		virtual ~SubMesh(void);


		void									Create(MeshPtr pMesh, int indexOffset, int indexCount, int vertexOffset, int vertexCount, int vertexStride, int matIndex, int primCount, PRIMITIVE_TYPE primType, const VertexFormat& vf, G_FORMAT indexFormat);

		void*									GetIndexData();
		void*									GetVertexData();
		
		int										GetIndexDataBytes();
		int										GetVertexDataBytes();

		int										GetIndexDataOffset();
		int										GetVertexDataOffset();
		int										GetIndexCount();
		int										GetVertexCount();
		int										GetVertexStride();

		MaterialPtr								GetMaterial();
		int										GetPrimitiveCount();
		PRIMITIVE_TYPE							GetPrimitiveType();
		bool									IsIndexed();

		const VertexFormat&						GetVertexFormat();
		G_FORMAT								GetIndexFormat();
	private:

		MeshPtr									m_pMesh;

		int										m_indexOffset;
		int										m_vertexOffset;

		int										m_vertexCount;
		int										m_indexCount;
		int										m_primitiveCount;
		int										m_materialIndex;
		int										m_vertexStride;
		PRIMITIVE_TYPE							m_primitiveType;
		bool									m_indexed;

		VertexFormat							m_vertexFormat;

		G_FORMAT								m_indexFormat;
		
	};


}
