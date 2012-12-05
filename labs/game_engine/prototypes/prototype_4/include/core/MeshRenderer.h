#pragma once

#include "core\GameObjectComponent.h"
#include "core\RenderData.h"


namespace engine
{
	namespace object_component
	{
		class EXPORT_CLASS MeshRenderer : public GameObjectComponent
		{
			class SubMeshRenderData : public RenderData
			{
			public:
				SubMeshRenderData(GameObjectPtr pGameObject);
				virtual ~SubMeshRenderData();

				void											Render_Depth(Sys_GraphicsPtr pSysGraphics);
				void											Render(Sys_GraphicsPtr pSysGraphics);
				MaterialPtr										GetMaterial();
				math::Matrix44									GetWorldMatrix();

				void											Create(GPUBufferPtr pIndexBuffer, 
																	GPUBufferPtr pVertexBuffer, 
																	MaterialPtr pMaterial, 
																	int indexCount,
																	int vertexOffset,
																	int vertexStride,
																	int startIndex,
																	int baseVertex);
			private:
				GameObjectPtr									m_pGameObject;

				MaterialPtr										m_pMaterial;
				GPUBufferPtr									m_pIndexBuffer;
				GPUBufferPtr									m_pVertexBuffer;
				int												m_vertexStride;
				int												m_vertexOffset;
				int												m_indexCount;
				int												m_startIndex;
				int												m_baseVertex;
				int												m_iDepthPass;
			};
		public:
			MeshRenderer();
			virtual ~MeshRenderer(void);

			void							Update();

			void							Reset(MeshDataPtr pMD);
			void							SetRenderSystem(RenderSystemPtr pRS);

			static MeshRendererPtr			CreateComponent();
		private:
			bool							OnAttach();
			void							OnDetach();
		private:

			RenderSystemPtr					m_pRS;

			GPUBufferPtr					m_pIndexBuffer;
			GPUBufferPtr					m_pVertexBuffer;

			typedef boost::shared_ptr<SubMeshRenderData>				SubMeshRenderDataPtr;
			std::vector<SubMeshRenderDataPtr>	m_Subsets;
		};

	}
}
