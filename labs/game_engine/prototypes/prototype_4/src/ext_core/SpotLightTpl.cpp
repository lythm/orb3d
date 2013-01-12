#include "core_ext_pch.h"
#include "SpotLightTpl.h"



namespace engine
{
	SpotLightTpl::SpotLightTpl(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Light")
	{
	}


	SpotLightTpl::~SpotLightTpl(void)
	{
	}
	GameObjectPtr SpotLightTpl::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject(L"Spot Light");

		GameObjectComponentPtr pLight = m_pManager->CreateComponent(L"SpotLight");
		pObj->AddComponent(pLight);

		return pObj;
	}
	void SpotLightTpl::Release()
	{
	}
}
