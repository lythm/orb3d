#pragma once


namespace engine
{
	class EXPORT_CLASS Mesh
	{
	public:

		class SubMesh
		{
		public:
			
			

		private:

			MeshPtr									m_pMesh;

			int										m_indexOffset;
			int										m_vertexOffset;

			int										m_vertexCount;
			int										m_indexCount;
			int										m_primitiveCount;
			int										m_materialIndex;
		};

		Mesh(void);
		virtual ~Mesh(void);

		void*										GetIndexData();
		void*										GetVertexData();
		GFXPtr										GetMaterialByIndex(int index);
		int											GetMaterialCount();

		bool										Create(int indexBufferSize, int vertexBufferSize, const std::vector<GFXPtr>& materialList);
	private:
		void*										m_pIndexData;
		void*										m_pVertexData;

		GPUBufferPtr								m_pIndexBuffer;
		GPUBufferPtr								m_pVertexBuffer;

		std::vector<GFXPtr>							m_materialList;
	};
}

