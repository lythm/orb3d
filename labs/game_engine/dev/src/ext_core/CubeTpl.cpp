#include "core_ext_pch.h"
#include "CubeTpl.h"

namespace ld3d
{
	CubeTpl::CubeTpl(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Geometry")
	{
	}


	CubeTpl::~CubeTpl(void)
	{
	}
	GameObjectPtr CubeTpl::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject(L"Cube");
		
		MeshDataPtr pMD = boost::shared_dynamic_cast<MeshData>(m_pManager->CreateComponent(L"MeshData"));
		pMD->SetMeshAsset(L"_cube_");

		pObj->AddComponent(pMD);

		MeshRendererPtr pMR = boost::shared_dynamic_cast<MeshRenderer>(m_pManager->CreateComponent(L"MeshRenderer"));
		pObj->AddComponent(pMR);

		return pObj;
	}
	void CubeTpl::Release()
	{
	}
}
