#include "core_pch.h"
#include "..\..\include\core\GameObjectManager.h"
#include "core\GameObject.h"

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

	bool GameObjectManager::Initialize(CoreApiPtr pCore)
	{
		m_pCore = pCore;
		if(false == LoadPackage(L"./core_ext.dll"))
		{
			return false;
		}


		return true;
	}
	void GameObjectManager::Release()
	{
		ReleaseAllObject();
		m_componentCreator.clear();
		for(size_t i = 0; i < m_packages.size(); ++i)
		{
			m_packages[i].delete_package();
		}
		m_packages.clear();
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
	bool GameObjectManager::LoadPackage(const std::wstring& name)
	{
		PackageMod mod;
		if(false == mod.load_package(name.c_str(), m_pCore))
		{
			return false;
		}
		mod.GetPackage()->RegisterPacket(this);
		m_packages.push_back(mod);
		return true;
	}
	int GameObjectManager::GetPackageCount()
	{
		return m_packages.size();
	}
	ExtPackage* GameObjectManager::GetPackageByIndex(int index)
	{
		return m_packages[index].GetPackage();
	}
}


namespace engine
{
	GameObjectManager::PackageMod::PackageMod()
	{
		m_pPackage			= nullptr;
		m_hLib				= nullptr;
	}
	ExtPackage* GameObjectManager::PackageMod::GetPackage()
	{
		return m_pPackage;
	}
	bool GameObjectManager::PackageMod::load_package(const wchar_t* file, CoreApiPtr pCore)
	{
		m_hLib = ::LoadLibrary(file);
		if(m_hLib == NULL)
		{
			return false;
		}


		Fn_CreatePackage CreatePackage = (Fn_CreatePackage)GetProcAddress(m_hLib, "CreatePackage");
		if(CreatePackage == NULL)
		{
			FreeLibrary(m_hLib);
			return false;
		}

		m_file = file;
		m_pPackage = CreatePackage(pCore);

		return true;
	}

	void GameObjectManager::PackageMod::delete_package()
	{
		if(m_hLib == NULL)
		{
			return;
		}
		Fn_DestroyPackage DestroyPackage = (Fn_DestroyPackage)GetProcAddress(m_hLib, "DestroyPackage");

		if(DestroyPackage == NULL)
		{
			return;

		}

		DestroyPackage(m_pPackage);

		FreeLibrary(m_hLib);
		m_hLib = NULL;
	}

}
