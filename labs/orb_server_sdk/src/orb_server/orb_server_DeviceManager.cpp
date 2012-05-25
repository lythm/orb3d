#include "orb_server_pch.h"
#include "orb_server_DeviceManager.h"
#include "orb_server_ServerApplication.h"


namespace orb
{

	DeviceManager::DeviceManager(void)
	{

	}

	DeviceManager::~DeviceManager(void)
	{
	}
	const std::vector<std::wstring>& DeviceManager::AppSettings(const std::wstring& key)
	{
		return GetCore()->AppSettings(key);
	}
	std::wstring DeviceManager::AppSettings(const std::wstring& key, int index)
	{
		return GetCore()->AppSettings(key, index);
	}
	DeviceManager::Result DeviceManager::LoadDevice(const w_char* dev)
	{
		DeviceInfo info;
		info.file = dev;
		info.lib = os::open_library(dev);
		if(info.lib == NULL)
		{
			return ret_failed;
		}

		PTR_ALLOC_DEVICE dev_alloc = (PTR_ALLOC_DEVICE)os::load_func(info.lib, FUNC_ALLOC_DEVICE_NAME);

		if(dev_alloc == NULL)
		{
			os::close_library(info.lib);
			return ret_failed;
		}

		info.pDevice = dev_alloc();
		if(info.pDevice == NULL)
		{
			os::close_library(info.lib);
			return ret_failed;
		}

		if(NULL != FindDevice(info.pDevice->GetId()))
		{
			if(GetCore()->AppSettings(L"ignore_device_conflict", 0) != L"Yes")
			{

				std::wstring msg = L"device id conflict, " + boost::lexical_cast<std::wstring>(info.pDevice->GetId());

				PrintSysMessage(msg);
				UnLoadDevice(info);
				return ret_failed;
			}

			PrintSysMessage(std::wstring(L"device id conflict,") + dev + L" ignored.");
			os::close_library(info.lib);
			return ret_ok;
		}

		std::wstring devName = info.pDevice->GetName();

		if(info.pDevice->Initialize(this) == false)
		{
			UnLoadDevice(info);

			if(GetCore()->AppSettings(L"ignore_device_load_failure", 0) != L"Yes")
			{
				PrintSysMessage(std::wstring(L"device failed to initialize ,") +devName + L"[" + dev + L"]");
				return ret_failed;
			}
			PrintSysMessage(std::wstring(L"device failed to initialize ,") + devName + L"[" + dev + L"] " + L" ignored.");
			return ret_ok;
		}

		PrintSysMessage(std::wstring(L"device ") + devName + L"[" + dev + L"]" + L" is on.");
		m_devs.push_back(info);

		return ret_ok;
	}
	void DeviceManager::UnLoadDevice(const DeviceInfo& d)
	{
		if(d.lib == 0)
			return;

		if(d.pDevice != NULL)
		{
			d.pDevice->Release();

			PTR_FREE_DEVICE dev_free = (PTR_FREE_DEVICE)os::load_func(d.lib, FUNC_FREE_DEVICE_NAME);

			if(dev_free)
			{
				dev_free(d.pDevice);
			}
		}

		os::close_library(d.lib);
		
	}

	DeviceManager::Result DeviceManager::Load()
	{
		const std::vector<std::wstring>& devices = GetCore()->AppSettings(L"device");


		for(size_t i = 0; i < devices.size(); ++i)
		{
			Result ret = LoadDevice(devices[i].c_str());
			if(ret != ret_ok)
			{
				PrintSysMessage(L"failed to load device " + devices[i]);

				if(GetCore()->AppSettings(L"ignore_device_load_failure", 0) == L"Yes")
				{
					continue;
				}
				else
				{
					return ret;
				}
			}
		}

		return ret_ok;
	}
	void DeviceManager::UnLoad()
	{
		for(size_t i = 0; i < m_devs.size(); ++i)
		{
			std::wstring devName = m_devs[i].pDevice->GetName();
			UnLoadDevice(m_devs[i]);
			PrintSysMessage(L"device " + devName + L"[" + m_devs[i].file + L"]" + L" is off.");
		}
		m_devs.clear();
	}
	Device* DeviceManager::FindDevice(uint32 id)
	{
		for(size_t i = 0; i < m_devs.size(); ++i)
		{
			if(m_devs[i].pDevice->GetId() == id)
				return m_devs[i].pDevice;
		}
		return NULL;
	}
	void DeviceManager::ListDevice()
	{
		for(size_t i = 0; i < m_devs.size(); ++i)
		{
			w_char tmp[100];

			swprintf(tmp, 100, L"device[%d]: %ls[%ls]", m_devs[i].pDevice->GetId(), m_devs[i].pDevice->GetName(), m_devs[i].file.c_str());

			PrintSysMessage(tmp);
		}

		w_char tmp[100];

		swprintf(tmp, 100, L"%d device installed.", m_devs.size());

		PrintSysMessage(tmp);
	}
}
