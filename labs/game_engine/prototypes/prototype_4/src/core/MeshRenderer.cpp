#include "core_pch.h"
#include "..\..\include\core\MeshRenderer.h"
#include "core\GameObject.h"
#include "core\MeshData.h"

namespace engine
{
	namespace object_component
	{
		MeshRenderer::MeshRenderer(RenderSystemPtr pRS) : GameObjectComponent(L"MeshRenderer")
		{
			m_pRS = pRS;
		}

		MeshRenderer::~MeshRenderer(void)
		{
		}
		void MeshRenderer::Update()
		{
			MeshDataPtr pData = boost::shared_dynamic_cast<MeshData>(m_pObject->GetComponent(L"MeshData"));
			MeshPtr pMesh = pData->GetMesh();


		}
		bool MeshRenderer::OnAttach()
		{
			if(m_pObject->GetComponent(L"MeshData") == NULL)
			{
				return false;
			}

			return true;
		}




		void MeshRenderer::SubMeshRenderData::Render(Sys_GraphicsPtr pSysGraphics)
		{
		}
		GFXPtr MeshRenderer::SubMeshRenderData::GetGFX()
		{
			return GFXPtr();
		}
		math::Matrix44 MeshRenderer::SubMeshRenderData::GetWorldMatrix()
		{
			return math::MatrixIdentity();
		}
	}

}
