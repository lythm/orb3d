#include "orb_server_pch.h"
#include "orb_server_MemManager.h"
#include "orb_server_DeviceManager.h"

namespace orb
{
	MemManager::MemManager(void)
	{
		m_pDevice				= NULL;
	}


	MemManager::~MemManager(void)
	{
	}

	MemManager::Result MemManager::Initialize(DeviceManager* pDeviceManager)
	{
		m_pDevice = (mem::MemDevice*)pDeviceManager->FindDevice(DeviceId::device_mem);

		if(m_pDevice == NULL)
			return ret_failed;

		return ret_ok;
	}
	void MemManager::Release()
	{
		m_pDevice = NULL;
	}
	void* MemManager::Alloc(uint32 bytes)
	{
		return m_pDevice->Alloc(bytes);
	}
	void MemManager::Free(void* mem)
	{
		m_pDevice->Free(mem);
	}
}