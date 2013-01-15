#include "core_ext_pch.h"
#include "DirLightTpl.h"


namespace ld3d
{
	DirLightTpl::DirLightTpl(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Light")
	{
	}


	DirLightTpl::~DirLightTpl(void)
	{
	}
	GameObjectPtr DirLightTpl::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject(L"Directional Light");

		GameObjectComponentPtr pLight = m_pManager->CreateComponent(L"DirectionalLight");
		pObj->AddComponent(pLight);

		return pObj;
	}
	void DirLightTpl::Release()
	{
	}
}
