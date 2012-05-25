#pragma once

namespace orb
{
	class DeviceManager;
	class SysConfig;
	class SMManager;
	class NetworkManager;
	class MemManager;

	class Core_Impl : public Core
	{
	public:
		Core_Impl(void);
		virtual ~Core_Impl(void);

		bool								Initialize();
		void								Release();

		const std::vector<std::wstring>&	AppSettings(const std::wstring& key);

		std::wstring						AppSettings(const std::wstring& key, int index);

		bool								InstallServiceMod(ServiceMod* pMod);
		void								UnInstallServiceMod(ServiceMod* pMod);
		
		void*								MemAlloc(uint32 bytes);
		void								MemFree(void* mem);


		ede::EventPtr						AllocEvent(uint32 bytes);

		void								ListSM();
		void								ListDevice();





	private:
		ede::EventDispatchEngine*			m_pEDE;
		SysConfig*							m_pSysConfig;
		DeviceManager*						m_pDeviceManager;
		SMManager*							m_pSMManager;

		MemManager*							m_pMem;

		NetworkManager*						m_pNetwork;
	};
}
