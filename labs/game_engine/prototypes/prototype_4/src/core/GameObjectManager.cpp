#include "core_pch.h"
#include "..\..\include\core\GameObjectManager.h"
#include "core\GameObject.h"


namespace engine
{
	GameObjectManager::GameObjectManager(void)
	{
		m_pRoot = GameObjectPtr(new GameObject);
	}

	GameObjectManager::~GameObjectManager(void)
	{
		ReleaseAllObject();

	}
	GameObjectPtr GameObjectManager::CreateObjectFromTemplate(const std::string& tpl)
	{
		return GameObjectPtr();
	}
	void GameObjectManager::RegisterObject()
	{

	}
	void GameObjectManager::UpdateObjects()
	{
		m_pRoot->Update();
	}
	GameObjectPtr GameObjectManager::GetRoot()
	{
		return m_pRoot;
	}
	void GameObjectManager::ReleaseAllObject()
	{
		if(m_pRoot)
		{
			m_pRoot->Clear();
			m_pRoot.reset();
		}
	}
	GameObjectComponentPtr GameObjectManager::CreateObjectComponent(const std::string& name)
	{
		return GameObjectComponentPtr();
	}
}
