#include "core_ext_pch.h"
#include "Tpl_Plane.h"

namespace ld3d
{
	Tpl_Plane::Tpl_Plane(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Geometry")
	{
	}


	Tpl_Plane::~Tpl_Plane(void)
	{
	}
	GameObjectPtr Tpl_Plane::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject(L"Plane");
		
		MeshDataPtr pMD = boost::shared_dynamic_cast<MeshData>(m_pManager->CreateComponent(L"MeshData"));
		pMD->SetMeshAsset(L"_plane_");

		pObj->AddComponent(pMD);

		MeshRendererPtr pMR = boost::shared_dynamic_cast<MeshRenderer>(m_pManager->CreateComponent(L"MeshRenderer"));
		pObj->AddComponent(pMR);

		return pObj;
	}
	void Tpl_Plane::Release()
	{
	}
}
