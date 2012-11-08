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

			void*									m_pIndexBuffer;
			void*									m_pVertexBuffer;

			int										m_vertexCount;
			int										m_indexCount;
			int										m_primitiveCount;

			GFXPtr									m_pGFX;
		};

		Mesh(void);
		virtual ~Mesh(void);

	private:
		void*										m_pIndexBuffer;
		void*										m_pVertexBuffer;

	};


}
