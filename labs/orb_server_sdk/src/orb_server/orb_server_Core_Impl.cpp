#include "orb_server_pch.h"
#include "orb_server_Core_Impl.h"
#include "orb_server_SysConfig.h"
#include "orb_server_DeviceManager.h"
#include "orb_server_SMManager.h"
#include "orb_server_NetworkManager.h"
#include "orb_server_MemManager.h"


namespace orb
{

	Core_Impl::Core_Impl(void)
	{
		m_pEDE						= NULL;
		m_pSysConfig				= NULL;
		m_pDeviceManager			= NULL;
		m_pSMManager				= NULL;

		m_pMem						= NULL;
		m_pNetwork					= NULL;

	}


	Core_Impl::~Core_Impl(void)
	{
	}
	std::wstring Core_Impl::AppSettings(const std::wstring& key, int index)
	{
		const std::vector<std::wstring>& v = AppSettings(key);

		if(index >= (int)v.size())
			return L"";

		return v[index];
	}
	const std::vector<std::wstring>& Core_Impl::AppSettings(const std::wstring& key)
	{
		return m_pSysConfig->Settings(key);
	}
	bool Core_Impl::Initialize()
	{
		m_pSysConfig = new SysConfig;

		if(false == m_pSysConfig->Load("./orb_sys.conf"))
		{
			return false;
		}


		m_pDeviceManager = new DeviceManager;

		if(m_pDeviceManager->Load() != DeviceManager::ret_ok)
		{
			return false;
		}

		m_pMem = new MemManager;

		if(m_pMem->Initialize(m_pDeviceManager) != MemManager::ret_ok)
		{
			return false;
		}
		
		m_pNetwork = new NetworkManager;

		if(m_pNetwork->Initialize(m_pDeviceManager) != NetworkManager::ret_ok)
		{
			return false;
		}

		m_pEDE = new ede::EventDispatchEngine;

		if(m_pEDE == NULL)
			return false;

		if(ede::ede_ret_ok != m_pEDE->Initialize())
			return false;


		m_pSMManager = new SMManager;

		if(m_pSMManager->Initialize() == false)
		{
			return false;
		}

		return true;
	}
	void Core_Impl::Release()
	{
		if(m_pSMManager)
		{
			m_pSMManager->Release();
			delete m_pSMManager;
			m_pSMManager = NULL;
		}
		if(m_pEDE)
		{
			m_pEDE->Release();
			delete m_pEDE;
			m_pEDE = NULL;
		}

		if(m_pNetwork)
		{
			m_pNetwork->Release();
			delete m_pNetwork;
			m_pNetwork = NULL;
		}

		if(m_pMem)
		{
			m_pMem->Release();
			delete m_pMem;
			m_pMem = NULL;
		}

		if(m_pDeviceManager)
		{
			m_pDeviceManager->UnLoad();
			delete m_pDeviceManager;
			m_pDeviceManager = NULL;
		}

		if(m_pSysConfig)
		{
			delete m_pSysConfig;
			m_pSysConfig = NULL;
		}
	}

	bool Core_Impl::InstallServiceMod(ServiceMod* pMod)
	{
		return true;
	}
	void Core_Impl::UnInstallServiceMod(ServiceMod* pMod)
	{
	}

	void* Core_Impl::MemAlloc(uint32 bytes)
	{
		return m_pMem->Alloc(bytes);
	}
	void Core_Impl::MemFree(void* mem)
	{
		m_pMem->Free(mem);
	}
	void Core_Impl::ListSM()
	{
		m_pSMManager->ListSM();
	}
	void Core_Impl::ListDevice()
	{
		m_pDeviceManager->ListDevice();
	}
	ede::EventPtr Core_Impl::AllocEvent(uint32 bytes)
	{
		ede::Event* pEvent = (ede::Event*)MemAlloc(bytes);

		return ede::EventPtr(pEvent);
	}
}
