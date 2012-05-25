#pragma once

namespace orb
{
	class DeviceManager : public DeviceHost
	{
		struct DeviceInfo
		{
			std::wstring							file;
			Device*									pDevice;
			kernel_object							lib;
		};

	public:
		DeviceManager(void);
		virtual ~DeviceManager(void);

		enum Result
		{
			ret_ok,
			ret_failed,
		};

		const std::vector<std::wstring>&			AppSettings(const std::wstring& key);
		std::wstring								AppSettings(const std::wstring& key, int index);

		Result										Load();
		void										UnLoad();
		
		Result										LoadDevice(const w_char* dev);
		void										UnLoadDevice(const DeviceInfo& d);

		Device*										FindDevice(uint32 id);

		void										ListDevice();
	private:
		
		std::vector<DeviceInfo>						m_devs;
	};
}
