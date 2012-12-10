#include "core_pch.h"
#include "..\..\include\core\MeshRenderer.h"
#include "core\GameObject.h"
#include "core\MeshData.h"
#include "core\RenderSystem.h"
#include "core\Sys_Graphics.h"
#include "core\Mesh.h"
#include "core\GPUBuffer.h"
#include "core\Material.h"
#include "core\SubMesh.h"
#include "core_utils.h"


namespace engine
{
	namespace object_component
	{

		MeshRendererPtr MeshRenderer::CreateComponent()
		{
			return alloc_object<MeshRenderer>();
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

			if(pMesh->GetIndexData() != nullptr)
			{
				m_pIndexBuffer = m_pRS->GetSysGraphics()->CreateBuffer(BT_INDEX_BUFFER, pMesh->GetIndexDataBytes(), pMesh->GetIndexData(), false);
			}
			m_pVertexBuffer = m_pRS->GetSysGraphics()->CreateBuffer(BT_VERTEX_BUFFER, pMesh->GetVertexDataBytes(), pMesh->GetVertexData(), false);

			for(int i = 0; i < pMesh->GetSubMeshCount(); ++i)
			{
				SubMeshPtr pSub = pMesh->GetSubMesh(i);

				SubMeshRenderDataPtr pSR = alloc_object<SubMeshRenderData, GameObjectPtr>(GetGameObject());
				pSR->Create(pSub, m_pIndexBuffer, m_pVertexBuffer);
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
		void MeshRenderer::SubMeshRenderData::Create(SubMeshPtr pSub, GPUBufferPtr pIndexBuffer, GPUBufferPtr pVertexBuffer)
		{
			m_pIndexBuffer					= pIndexBuffer;
			m_pVertexBuffer					= pVertexBuffer;
			m_pMaterial						= pSub->GetMaterial();
			m_indexCount					= pSub->GetIndexCount();
			m_baseVertex					= 0;
			m_vertexOffset					= pSub->GetVertexDataOffset();
			m_vertexStride					= pSub->GetVertexStride();
			m_startIndex					= 0;
			m_vertexCount					= pSub->GetVertexCount();
			m_iDepthPass					= m_pMaterial->FindPass("DEPTH_PASS");
			m_primType						= pSub->GetPrimitiveType();
			m_indexed						= pSub->IsIndexed();
			m_vertexFormat					= pSub->GetVertexFormat();
			m_indexFormat					= pSub->GetIndexFormat();
		}
		void MeshRenderer::SubMeshRenderData::Render(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial)
		{
			pSysGraphics->SetVertexBuffer(m_pVertexBuffer, m_vertexOffset, m_vertexStride);
			pSysGraphics->SetPrimitiveType(m_primType);
			
			m_indexed ? pSysGraphics->SetIndexBuffer(m_pIndexBuffer, m_indexFormat) : 0;
			
			MaterialPtr pMat = pMaterial == nullptr ? m_pMaterial : pMaterial;

			pMat->ApplyVertexFormat();

			int nPass = 0;

			pMat->BeginPass(nPass);

			for(int i = 0; i < nPass; ++i)
			{
				if(m_iDepthPass == i)
				{
					continue;
				}
				pMat->ApplyPass(i);

				m_indexed ? 
					pSysGraphics->DrawIndexed(m_indexCount, m_startIndex, m_baseVertex) :
					pSysGraphics->Draw(m_vertexCount, m_baseVertex);
			}

			pMat->EndPass();
		}
		void MeshRenderer::SubMeshRenderData::Render_Depth(Sys_GraphicsPtr pSysGraphics)
		{
			pSysGraphics->SetVertexBuffer(m_pVertexBuffer, m_vertexOffset, m_vertexStride);
			pSysGraphics->SetPrimitiveType(m_primType);

			m_pMaterial->ApplyVertexFormat();
			m_indexed ? pSysGraphics->SetIndexBuffer(m_pIndexBuffer, G_FORMAT_R16_UINT) : 0;

			int nPass = 0;

			m_pMaterial->BeginPass(nPass);

			m_pMaterial->ApplyPass(m_iDepthPass);

			m_indexed ? 
					pSysGraphics->DrawIndexed(m_indexCount, m_startIndex, m_baseVertex) :
					pSysGraphics->Draw(m_vertexCount, m_baseVertex);

						
			m_pMaterial->EndPass();
		}
		MaterialPtr MeshRenderer::SubMeshRenderData::GetMaterial()
		{
			return m_pMaterial;
		}
		math::Matrix44 MeshRenderer::SubMeshRenderData::GetWorldMatrix()
		{
			return m_pGameObject->GetWorldTransform();
		}
		bool MeshRenderer::SubMeshRenderData::IsDeferred()
		{
			return true;
		}

	}
}
