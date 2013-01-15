#include "core_ext_pch.h"
#include "CubeTpl.h"

namespace engine
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
		
		RenderSystemPtr pRS = m_pManager->GetRenderSystem();


		MaterialPtr pMaterial = pRS->CreateMaterialFromFile("./assets/standard/material/editor_shape.fx");
		MeshPtr pMesh = MeshUtil::CreateCube(2, pMaterial);

		MeshDataPtr pMD = boost::shared_dynamic_cast<MeshData>(m_pManager->CreateComponent(L"MeshData"));
		pMD->SetMesh(pMesh);

		pObj->AddComponent(pMD);

		MeshRendererPtr pMR = boost::shared_dynamic_cast<MeshRenderer>(m_pManager->CreateComponent(L"MeshRenderer"));
		pObj->AddComponent(pMR);

		return pObj;
	}
	void CubeTpl::Release()
	{
	}
}
