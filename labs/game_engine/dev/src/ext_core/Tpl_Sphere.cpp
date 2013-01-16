#include "core_ext_pch.h"
#include "Tpl_Sphere.h"

namespace ld3d
{
	Tpl_Sphere::Tpl_Sphere(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Geometry")
	{
	}


	Tpl_Sphere::~Tpl_Sphere(void)
	{
	}
	void Tpl_Sphere::Release()
	{
	}
	GameObjectPtr Tpl_Sphere::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject(L"Sphere");
		
		MeshDataPtr pMD = boost::shared_dynamic_cast<MeshData>(m_pManager->CreateComponent(L"MeshData"));
		pMD->SetMeshAsset(L"_sphere_");

		pObj->AddComponent(pMD);

		MeshRendererPtr pMR = boost::shared_dynamic_cast<MeshRenderer>(m_pManager->CreateComponent(L"MeshRenderer"));
		pObj->AddComponent(pMR);

		return pObj;
	}
}