#include "core_ext_pch.h"
#include "Tpl_DirLight.h"


namespace ld3d
{
	Tpl_DirLight::Tpl_DirLight(GameObjectManagerPtr pManager, const std::wstring& name) : GameObjectTemplate(pManager, name, L"Light")
	{
	}


	Tpl_DirLight::~Tpl_DirLight(void)
	{
	}
	GameObjectPtr Tpl_DirLight::CreateGameObject()
	{
		GameObjectPtr pObj = m_pManager->CreateGameObject(L"Directional Light");

		GameObjectComponentPtr pLight = m_pManager->CreateComponent(L"DirectionalLight");
		pObj->AddComponent(pLight);

		return pObj;
	}
	void Tpl_DirLight::Release()
	{
	}
}
