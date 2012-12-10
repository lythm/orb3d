#include "core_pch.h"
#include "..\..\include\core\GameObjectManager.h"
#include "core\GameObject.h"

#include "core\meshdata.h"
#include "core\meshrenderer.h"
#include "core_utils.h"


namespace engine
{
	GameObjectManager::GameObjectManager(void)
	{
		m_pRoot = alloc_object<GameObject, wchar_t*>(L"_root");
	}

	GameObjectManager::~GameObjectManager(void)
	{
		ReleaseAllObject();
	}

	bool GameObjectManager::Initialize()
	{
		RegisterBuildinComponents();

		return true;
	}
	void GameObjectManager::Release()
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
		}
	}
	GameObjectComponentPtr GameObjectManager::CreateComponent(const std::wstring& name)
	{
		if(m_componentCreator.find(name) == m_componentCreator.end())
		{
			return GameObjectComponentPtr();
		}

		return m_componentCreator[name]();
	}
	void GameObjectManager::RegisterBuildinComponents()
	{
		using namespace object_component;
		RegisterComponent(L"MeshData", MeshData::CreateComponent);
		RegisterComponent(L"MeshRenderer", MeshRenderer::CreateComponent);
	}
	GameObjectPtr GameObjectManager::CreateGameObject(const std::wstring& name)
	{
		GameObjectPtr pObj = alloc_object<GameObject>();
		pObj->SetName(name);

		pObj->LinkTo(m_pRoot);
		return pObj;
	}
	void GameObjectManager::WalkObjectTree()
	{
		if(m_pRoot == NULL)
		{
			return;
		}
	}
	void GameObjectManager::_tree_walk(GameObject* pObj)
	{

	}
	void GameObjectManager::RegisterComponent(const std::wstring& name, const ComponentCreator& creator )
	{
		m_componentCreator[name] = creator;
	}
}
