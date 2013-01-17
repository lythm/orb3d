#pragma once

#include "core\GameObjectComponent.h"
#include "core\RenderData.h"
#include "core\g_format.h"
#include "core\VertexFormat.h"

namespace ld3d
{

	class EXPORT_CLASS MeshRenderer : public GameObjectComponent
	{
		class SubMeshRenderData : public RenderData
		{
		public:
			SubMeshRenderData(GameObjectPtr pGameObject);
			virtual ~SubMeshRenderData();

			void											Render_Depth(Sys_GraphicsPtr pSysGraphics);
			void											Render(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial = MaterialPtr());
			MaterialPtr										GetMaterial();
			math::Matrix44									GetWorldMatrix();

			void											Create(SubMeshPtr pSub, GPUBufferPtr pIndexBuffer, GPUBufferPtr pVertexBuffer);
			bool											IsDeferred();
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
			bool											m_indexed;
			PRIMITIVE_TYPE									m_primType;
			int												m_vertexCount;

			VertexFormat									m_vertexFormat;
			G_FORMAT										m_indexFormat;
		};
	public:
		MeshRenderer(GameObjectManagerPtr pManager);
		virtual ~MeshRenderer(void);

		void							Update();

		void							Reset(MeshDataPtr pMD);
		const bool&						IsDeferred();
		void							SetDeferred(const bool& b);

		RenderSystemPtr					GetRenderSystem(){return m_pRS;}

		const Version&					GetVersion() const;
	private:
		bool							OnAttach();
		void							OnDetach();
	private:

		RenderSystemPtr					m_pRS;

		GPUBufferPtr					m_pIndexBuffer;
		GPUBufferPtr					m_pVertexBuffer;

		typedef boost::shared_ptr<SubMeshRenderData>				SubMeshRenderDataPtr;
		std::vector<SubMeshRenderDataPtr>	m_Subsets;

		bool							m_deferred;
	};

}
