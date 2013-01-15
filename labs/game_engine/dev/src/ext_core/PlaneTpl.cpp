#include "core_ext_pch.h"
#include "PlaneTpl.h"

namespace ld3d
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
		
		MeshDataPtr pMD = boost::shared_dynamic_cast<MeshData>(m_pManager->CreateComponent(L"MeshData"));
		pMD->SetMeshAsset(L"_plane_");

		pObj->AddComponent(pMD);

		MeshRendererPtr pMR = boost::shared_dynamic_cast<MeshRenderer>(m_pManager->CreateComponent(L"MeshRenderer"));
		pObj->AddComponent(pMR);

		return pObj;
	}
	void PlaneTpl::Release()
	{
	}
}
