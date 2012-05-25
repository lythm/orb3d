#include "orb_server_pch.h"
#include "orb_server_NetworkManager.h"
#include "orb_server_DeviceManager.h"

namespace orb
{
	NetworkManager::NetworkManager(void)
	{
		m_pDevice = NULL;
	}


	NetworkManager::~NetworkManager(void)
	{
	}
	NetworkManager::Result NetworkManager::Initialize(DeviceManager* pDeviceManager)
	{
		using namespace network;
		m_pDevice = (network::NetworkDevice*)pDeviceManager->FindDevice(DeviceId::device_network);

		if(m_pDevice == NULL)
			return ret_failed;
		
		return ret_ok;

	}
	void NetworkManager::Release()
	{
		m_pDevice = NULL;
	}

}