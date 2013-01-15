#include "core_ext_pch.h"
#include "PlaneTpl.h"

namespace engine
{
	PlaneTpl::PlaneTpl(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Geometry")
	{
	}


	PlaneTpl::~PlaneTpl(void)
	{
	}
	GameObjectPtr PlaneTpl::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject(L"Plane");
		
		RenderSystemPtr pRS = m_pManager->GetRenderSystem();


		MaterialPtr pMaterial = pRS->CreateMaterialFromFile("./assets/standard/material/editor_shape.fx");
		MeshPtr pMesh = MeshUtil::CreatePlane(100, pMaterial);

		MeshDataPtr pMD = boost::shared_dynamic_cast<MeshData>(m_pManager->CreateComponent(L"MeshData"));
		pMD->SetMesh(pMesh);

		pObj->AddComponent(pMD);

		MeshRendererPtr pMR = boost::shared_dynamic_cast<MeshRenderer>(m_pManager->CreateComponent(L"MeshRenderer"));
		pObj->AddComponent(pMR);

		return pObj;
	}
	void PlaneTpl::Release()
	{
	}
}