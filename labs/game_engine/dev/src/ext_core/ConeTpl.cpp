#include "core_ext_pch.h"
#include "ConeTpl.h"

namespace ld3d
{
	ConeTpl::ConeTpl(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Geometry")
	{
	}


	ConeTpl::~ConeTpl(void)
	{
	}
	GameObjectPtr ConeTpl::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject(L"Cone");
		
		MeshDataPtr pMD = boost::shared_dynamic_cast<MeshData>(m_pManager->CreateComponent(L"MeshData"));
		pMD->SetMeshAsset(L"_cone_");

		pObj->AddComponent(pMD);

		MeshRendererPtr pMR = boost::shared_dynamic_cast<MeshRenderer>(m_pManager->CreateComponent(L"MeshRenderer"));
		pObj->AddComponent(pMR);

		return pObj;
	}
	void ConeTpl::Release()
	{
	}

}