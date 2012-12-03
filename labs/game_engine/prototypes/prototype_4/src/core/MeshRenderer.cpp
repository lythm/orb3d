#include "core_pch.h"
#include "..\..\include\core\MeshRenderer.h"
#include "core\GameObject.h"
#include "core\MeshData.h"
#include "core\RenderSystem.h"
#include "core\Sys_Graphics.h"
#include "core\Mesh.h"
#include "core\GPUBuffer.h"
#include "core\GFX.h"
#include "core\SubMesh.h"

namespace engine
{
	namespace object_component
	{

		MeshRendererPtr MeshRenderer::CreateComponent()
		{
			return MeshRendererPtr(new MeshRenderer);
		}

		MeshRenderer::MeshRenderer() : GameObjectComponent(L"MeshRenderer")
		{
			
		}

		MeshRenderer::~MeshRenderer(void)
		{
		}
		void MeshRenderer::Update()
		{
			for(size_t i = 0; i < m_Subsets.size(); ++i)
			{
				m_pRS->AddRenderData(m_Subsets[i]);
			}
		}
		void MeshRenderer::SetRenderSystem(RenderSystemPtr pRS)
		{
			m_pRS = pRS;
		}
		bool MeshRenderer::OnAttach()
		{
			MeshDataPtr pMD = boost::shared_dynamic_cast<MeshData>(m_pObject->GetComponent(L"MeshData"));

			Reset(pMD);


			return true;
		}
		void MeshRenderer::OnDetach()
		{
			m_pRS.reset();

			if(m_pIndexBuffer)
			{
				m_pIndexBuffer->Release();
				m_pIndexBuffer.reset();
			}
			if(m_pVertexBuffer)
			{
				m_pVertexBuffer->Release();
				m_pVertexBuffer.reset();
			}

			m_Subsets.clear();
		}
		void MeshRenderer::Reset(MeshDataPtr pMD)
		{
			if(pMD == NULL)
			{
				return;
			}

			MeshPtr pMesh = pMD->GetMesh();

			m_pIndexBuffer = m_pRS->GetSysGraphics()->CreateBuffer(BT_INDEX_BUFFER, pMesh->GetIndexDataBytes(), pMesh->GetIndexData(), false);
			m_pVertexBuffer = m_pRS->GetSysGraphics()->CreateBuffer(BT_VERTEX_BUFFER, pMesh->GetVertexDataBytes(), pMesh->GetVertexData(), false);

			for(int i = 0; i < pMesh->GetSubMeshCount(); ++i)
			{
				SubMeshPtr pSub = pMesh->GetSubMesh(i);

				SubMeshRenderDataPtr pSR = SubMeshRenderDataPtr(new SubMeshRenderData(GetGameObject()));
				pSR->Create(m_pIndexBuffer, m_pVertexBuffer, pSub->GetMaterial(), pSub->GetIndexCount(), pSub->GetVertexDataOffset(), pSub->GetVertexStride(), 0, 0);

				m_Subsets.push_back(pSR);
			}
		}


		MeshRenderer::SubMeshRenderData::SubMeshRenderData(GameObjectPtr pGameObject)
		{
			m_pGameObject	= pGameObject;
			m_iDepthPass	= -1;;
			
			m_indexCount					= 0;
			m_baseVertex					= 0;
			m_vertexOffset					= 0;
			m_vertexStride					= 0;
			m_startIndex					= 0;

		}
		MeshRenderer::SubMeshRenderData::~SubMeshRenderData()
		{
			m_pGameObject.reset();
		}
		void MeshRenderer::SubMeshRenderData::Create(GPUBufferPtr pIndexBuffer, 
																	GPUBufferPtr pVertexBuffer, 
																	GFXPtr pGFX, 
																	int indexCount,
																	int vertexOffset,
																	int vertexStride,
																	int startIndex,
																	int baseVertex)
		{
			m_pIndexBuffer					= pIndexBuffer;
			m_pVertexBuffer					= pVertexBuffer;
			m_pGFX							= pGFX;
			m_indexCount					= indexCount;
			m_baseVertex					= baseVertex;
			m_vertexOffset					= vertexOffset;
			m_vertexStride					= vertexStride;
			m_startIndex					= startIndex;

			m_iDepthPass					= m_pGFX->FindPass("DEPTH_PASS");
		}
		void MeshRenderer::SubMeshRenderData::Render(Sys_GraphicsPtr pSysGraphics)
		{
			pSysGraphics->SetIndexBuffer(m_pIndexBuffer, G_FORMAT_R16_UINT);
			pSysGraphics->SetVertexBuffer(m_pVertexBuffer, m_vertexOffset, m_vertexStride);
			pSysGraphics->SetPrimitiveType(PT_TRIANGLE_LIST);

			m_pGFX->ApplyVertexFormat();


			int nPass = 0;

			m_pGFX->BeginPass(nPass);

			for(int i = 0; i < nPass; ++i)
			{
				if(m_iDepthPass == i)
				{
					continue;
				}
				m_pGFX->ApplyPass(i);

				pSysGraphics->DrawPrimitive(m_indexCount, m_startIndex, m_baseVertex);
			}

			m_pGFX->EndPass();
		}
		void MeshRenderer::SubMeshRenderData::Render_Depth(Sys_GraphicsPtr pSysGraphics)
		{
			pSysGraphics->SetIndexBuffer(m_pIndexBuffer, G_FORMAT_R16_UINT);
			pSysGraphics->SetVertexBuffer(m_pVertexBuffer, m_vertexOffset, m_vertexStride);
			pSysGraphics->SetPrimitiveType(PT_TRIANGLE_LIST);

			m_pGFX->ApplyVertexFormat();


			int nPass = 0;

			m_pGFX->BeginPass(nPass);

			m_pGFX->ApplyPass(m_iDepthPass);

			pSysGraphics->DrawPrimitive(m_indexCount, m_startIndex, m_baseVertex);
			
			m_pGFX->EndPass();
		}
		GFXPtr MeshRenderer::SubMeshRenderData::GetGFX()
		{
			return m_pGFX;
		}
		math::Matrix44 MeshRenderer::SubMeshRenderData::GetWorldMatrix()
		{
			return m_pGameObject->GetWorldTransform();
		}

	}
}
