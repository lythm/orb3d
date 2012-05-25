#pragma once

namespace orb
{
	class DeviceManager;

	class NetworkManager
	{
	public:
		NetworkManager();
		virtual ~NetworkManager(void);

		enum Result
		{
			ret_ok,
			ret_failed,
		};

		Result								Initialize(DeviceManager* pDeviceManager);
		void								Release();

	private:
		network::NetworkDevice*				m_pDevice;
	};
}
