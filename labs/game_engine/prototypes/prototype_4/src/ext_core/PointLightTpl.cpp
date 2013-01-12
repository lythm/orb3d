#include "core_ext_pch.h"
#include "PointLightTpl.h"



namespace engine
{
	PointLightTpl::PointLightTpl(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Light")
	{
	}


	PointLightTpl::~PointLightTpl(void)
	{
	}
	GameObjectPtr PointLightTpl::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject(L"Point Light");

		GameObjectComponentPtr pLight = m_pManager->CreateComponent(L"PointLight");
		pObj->AddComponent(pLight);

		return pObj;
	}
	void PointLightTpl::Release()
	{
	}
}
