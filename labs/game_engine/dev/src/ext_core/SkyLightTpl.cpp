#include "core_ext_pch.h"
#include "SkyLightTpl.h"


namespace engine
{
	SkyLightTpl::SkyLightTpl(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Light")
	{
	}


	SkyLightTpl::~SkyLightTpl(void)
	{
	}
	GameObjectPtr SkyLightTpl::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject(L"Sky Light");

		GameObjectComponentPtr pLight = m_pManager->CreateComponent(L"SkyLight");
		pObj->AddComponent(pLight);

		return pObj;
	}
	void SkyLightTpl::Release()
	{
	}
}
