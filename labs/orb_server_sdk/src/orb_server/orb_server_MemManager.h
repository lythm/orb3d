#pragma once

namespace orb
{
	class DeviceManager;

	class MemManager
	{
	public:
		MemManager(void);
		virtual ~MemManager(void);

		enum Result
		{
			ret_ok,
			ret_failed,
		};

		Result								Initialize(DeviceManager* pDeviceManager);
		void								Release();

		void*								Alloc(uint32 bytes);
		void								Free(void* mem);

	private:
		mem::MemDevice*						m_pDevice;
	};
}