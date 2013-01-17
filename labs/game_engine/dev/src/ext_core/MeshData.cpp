#include "core_ext_pch.h"
#include "..\..\include\core\ext\MeshData.h"
#include "core\Mesh.h"
#include "core\ext\MeshRenderer.h"
#include "core\GameObject.h"
#include "core\ext\PropertyManager.h"
#include "core\MeshUtil.h"
#include "core\RenderSystem.h"
#include "core\Sys_Graphics.h"

#include "CorePackage.h"

namespace ld3d
{

	MeshData::MeshData(GameObjectManagerPtr pManager) : GameObjectComponent(L"MeshData", pManager)
	{
		m_pMesh = MeshPtr();
	}


	MeshData::~MeshData(void)
	{

	}
	const Version& MeshData::GetVersion() const
	{
		return g_packageVersion;
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

		pPM->RegisterProperty<std::wstring, MeshData>(this,
			L"MeshAsset", 
			&MeshData::GetMeshAsset,
			&MeshData::SetMeshAsset);

		pPM->End();

		return true;
	}
	void MeshData::SetMeshAsset(const std::wstring& asset)
	{
		m_meshAsset = asset;
	
		if(m_pMesh != nullptr)
		{
			m_pMesh->Destroy();	
		}

		if(m_meshAsset == L"_cube_")
		{
			MaterialPtr pMaterial = m_pManager->GetRenderSystem()->GetSysGraphics()->CreateMaterialFromFile("./assets/standard/material/editor_shape.fx");
			MeshPtr pMesh = MeshUtil::CreateCube(1, pMaterial);
			m_pMesh = pMesh;
			ResetMeshRenderer();
		}
		else if(m_meshAsset == L"_sphere_")
		{
			MaterialPtr pMaterial = m_pManager->GetRenderSystem()->GetSysGraphics()->CreateMaterialFromFile("./assets/standard/material/editor_shape.fx");
			MeshPtr pMesh = MeshUtil::CreateSphere(1, 50, 50, pMaterial);
			m_pMesh = pMesh;
			ResetMeshRenderer();
		}
		else if(m_meshAsset == L"_cone_")
		{
			
			MaterialPtr pMaterial = m_pManager->GetRenderSystem()->GetSysGraphics()->CreateMaterialFromFile("./assets/standard/material/editor_shape.fx");
			MeshPtr pMesh = MeshUtil::CreateCone(1, 30, 50, pMaterial);
			m_pMesh = pMesh;
			ResetMeshRenderer();
		}
		else if(m_meshAsset == L"_plane_")
		{
						
			MaterialPtr pMaterial = m_pManager->GetRenderSystem()->GetSysGraphics()->CreateMaterialFromFile("./assets/standard/material/editor_shape.fx");
			MeshPtr pMesh = MeshUtil::CreatePlane(100, pMaterial);
			m_pMesh = pMesh;
			ResetMeshRenderer();
		}
		else
		{
			// load mesh assets
			LoadMesh(m_meshAsset);
		}
	}
	const std::wstring& MeshData::GetMeshAsset()
	{
		return m_meshAsset;
	}

	bool MeshData::LoadMesh(const std::wstring& asset)
	{
		return true;
	}

	bool MeshData::OnSerialize(DataStream* pStream)
	{
		pStream->WriteString(m_meshAsset);
		return true;
	}
	bool MeshData::OnUnSerialize(DataStream* pStream, const Version& version)
	{
		if(version != GetVersion())
		{
			return false;
		}
		pStream->ReadString(m_meshAsset);

		SetMeshAsset(m_meshAsset);

		return true;
	}
}

