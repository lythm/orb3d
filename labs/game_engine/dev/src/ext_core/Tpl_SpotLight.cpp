#include "core_ext_pch.h"
#include "Tpl_SpotLight.h"



namespace ld3d
{
	Tpl_SpotLight::Tpl_SpotLight(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Light")
	{
	}


	Tpl_SpotLight::~Tpl_SpotLight(void)
	{
	}
	GameObjectPtr Tpl_SpotLight::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject(L"Spot Light");

		GameObjectComponentPtr pLight = m_pManager->CreateComponent(L"SpotLight");
		pObj->AddComponent(pLight);

		return pObj;
	}
	void Tpl_SpotLight::Release()
	{
	}
}
