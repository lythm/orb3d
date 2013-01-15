#pragma once


namespace ld3d
{
	class EXPORT_CLASS Mesh
	{
	public:

		Mesh(void);
		virtual ~Mesh(void);

		int											GetIndexDataBytes();
		int											GetVertexDataBytes();
		void*										GetIndexData();
		void*										GetVertexData();
		MaterialPtr									GetMaterialByIndex(int index);
		int											GetMaterialCount();

		bool										Create(int indexBufferSize, void* pIndexBuffer, int vertexBufferSize, void* pVertexBuffer, const std::vector<MaterialPtr>& materialList);
		void										AddSubMesh(SubMeshPtr pSub);

		int											GetSubMeshCount();
		SubMeshPtr									GetSubMesh(int index);
		void										Destroy();
		void										Update();
	private:
		void*										m_pIndexData;
		int											m_indexDataBytes;
		void*										m_pVertexData;
		int											m_vertexDataBytes;
		
		std::vector<MaterialPtr>					m_materialList;
		std::vector<SubMeshPtr>						m_submeshList;
	};
}

