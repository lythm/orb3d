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
		m_pRoot->ClearChildren();


	}
	GameObjectPtr	GameObjectManager::CreateObject()
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
}
