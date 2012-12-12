#include "core_pch.h"
#include "..\..\include\core\MeshData.h"
#include "core\Mesh.h"
#include "core\MeshRenderer.h"
#include "core\GameObject.h"
#include "core_utils.h"
#include "core\PropertyManager.h"


namespace engine
{
	namespace object_component
	{
		MeshDataPtr MeshData::CreateComponent()
		{
			return alloc_object<MeshData>();
		}


		MeshData::MeshData() : GameObjectComponent(L"MeshData")
		{
			m_pMesh = MeshPtr();
		}


		MeshData::~MeshData(void)
		{
			
		}
		void MeshData::Update()
		{
			if(m_pMesh)
			{
				m_pMesh->Update();
			}
		}
		void MeshData::OnDetach()
		{
			if(m_pMesh)
			{
				m_pMesh->Destroy();
			}

		}
		MeshPtr	MeshData::GetMesh()
		{
			return m_pMesh;
		}
		void MeshData::SetMesh(MeshPtr pMesh)
		{
			if(m_pMesh)
			{
				m_pMesh->Destroy();
				m_pMesh.reset();
			}
			m_pMesh = pMesh;

			ResetMeshRenderer();
		}
		void MeshData::ResetMeshRenderer()
		{
			if(m_pObject == NULL)
			{
				return;
			}
			MeshRendererPtr pMR = boost::shared_dynamic_cast<MeshRenderer>(m_pObject->GetComponent(L"MeshRenderer"));
			if(pMR)
			{
				pMR->Reset(boost::shared_dynamic_cast<MeshData>(shared_from_this()));
			}
		}
		bool MeshData::OnAttach()
		{
			ResetMeshRenderer();

			PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));
			pPM->Begin(L"MeshData");

			pPM->RegisterProperty(L"Mesh", m_pMesh.get());

			pPM->End();

			return true;
		}
		bool MeshData::LoadMesh()
		{
			return true;
		}
	}
}
