#include "core_ext_pch.h"
#include "Tpl_Cube.h"

namespace ld3d
{
	Tpl_Cube::Tpl_Cube(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Geometry")
	{
	}
	 

	Tpl_Cube::~Tpl_Cube(void)
	{
	}
	GameObjectPtr Tpl_Cube::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject(L"Cube");
		
		MeshDataPtr pMD = boost::shared_dynamic_cast<MeshData>(m_pManager->CreateComponent(L"MeshData"));
		pMD->SetMeshAsset(L"_cube_");

		pObj->AddComponent(pMD);

		MeshRendererPtr pMR = boost::shared_dynamic_cast<MeshRenderer>(m_pManager->CreateComponent(L"MeshRenderer"));
		pObj->AddComponent(pMR);

		return pObj;
	}
	void Tpl_Cube::Release()
	{
	}
}
