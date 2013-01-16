#include "core_ext_pch.h"
#include "Tpl_SkyLight.h"


namespace ld3d
{
	Tpl_SkyLight::Tpl_SkyLight(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Light")
	{
	}


	Tpl_SkyLight::~Tpl_SkyLight(void)
	{
	}
	GameObjectPtr Tpl_SkyLight::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject(L"Sky Light");

		GameObjectComponentPtr pLight = m_pManager->CreateComponent(L"SkyLight");
		pObj->AddComponent(pLight);

		return pObj;
	}
	void Tpl_SkyLight::Release()
	{
	}
}
