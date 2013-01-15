#include "core_ext_pch.h"
#include "SphereTpl.h"

namespace ld3d
{
	SphereTpl::SphereTpl(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Geometry")
	{
	}


	SphereTpl::~SphereTpl(void)
	{
	}
	void SphereTpl::Release()
	{
	}
	GameObjectPtr SphereTpl::CreateGameObject()
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