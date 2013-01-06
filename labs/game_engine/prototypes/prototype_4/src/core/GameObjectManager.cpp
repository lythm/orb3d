#include "core_pch.h"
#include "..\..\include\core\GameObjectManager.h"
#include "core\GameObject.h"

#include "core_utils.h"


namespace engine
{
	GameObjectManager::GameObjectManager(void)
	{
	}

	GameObjectManager::~GameObjectManager(void)
	{
	}

	bool GameObjectManager::Initialize(CoreApiPtr pCore)
	{
		m_pCore = pCore;

		m_componentClasses.clear();

		if(false == LoadPackage(L"./core_ext.dll"))
		{
			return false;
		}

		return true;
	}
	void GameObjectManager::Release()
	{
		m_componentClasses.clear();
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
	
	GameObjectComponentPtr GameObjectManager::CreateComponent(const std::wstring& name)
	{
		if(m_componentClasses.find(name) == m_componentClasses.end())
		{
			return GameObjectComponentPtr();
		}

		return m_componentClasses[name]->m_creator(shared_from_this());
	}
	
	GameObjectPtr GameObjectManager::CreateGameObject(const std::wstring& name)
	{
		GameObjectPtr pObj = alloc_object<GameObject>();
		pObj->SetName(name);

		return pObj;
	}
	
	
	bool GameObjectManager::LoadPackage(const std::wstring& name)
	{
		PackageMod mod;
		if(false == mod.load_package(name.c_str(), m_pCore))
		{
			return false;
		}
		
		RegisterPackage(mod.GetPackage());
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
	bool GameObjectManager::RegisterComponentClass(ExtPackage::ComponentClass* c)
	{
		if(m_componentClasses.find(c->m_name) != m_componentClasses.end())
		{
			return false;
		}
		m_componentClasses[c->m_name] = c;
		return true;
	}
	bool GameObjectManager::RegisterPackage(ExtPackage* pPack)
	{
		for(int i = 0; i < pPack->GetClassCount(); ++i)
		{
			ExtPackage::ComponentClass* c = pPack->GetClassByIndex(i);
			RegisterComponentClass(c);
		}
		return true;
	}
	RenderSystemPtr	GameObjectManager::GetRenderSystem()
	{
		return m_pCore->GetRenderSystem();
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
