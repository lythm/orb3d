#include "core_pch.h"
#include "GameObjectManager.h"


namespace engine
{
	GameObjectManager::GameObjectManager(void)
	{
	}


	GameObjectManager::~GameObjectManager(void)
	{
	}
	bool GameObjectManager::RegisterComponents()
	{
		return true;
	}

	bool GameObjectManager::LoadExtension(const char* szFile)
	{
		return true;
	}

	void GameObjectManager::Release()
	{
	}

	GameObjectPtr GameObjectManager::CreateGameObject()
	{
		return GameObjectPtr();
	}
	GameObjectComponentPtr GameObjectManager::CreateComponent()
	{
		return GameObjectComponentPtr();
	}
}
