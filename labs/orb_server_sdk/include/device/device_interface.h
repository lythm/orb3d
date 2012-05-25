#pragma once

#include "types/orb_types.h"

namespace orb
{
	class DeviceHost
	{
	public:
		virtual const std::vector<std::wstring>&	AppSettings(const std::wstring& key)						= 0;
		virtual std::wstring						AppSettings(const std::wstring& key, int index)				= 0;

	protected:
		DeviceHost(){}
		virtual ~DeviceHost(){}
	};


	class Device
	{
	public:

		uint32							GetId()
		{
			return m_id;
		}

		virtual const w_char*			GetName()												= 0;
		virtual bool					Initialize(DeviceHost* pHost)							= 0;
		virtual void					Release()												= 0;

	protected:
		Device(uint32 id)
		{
			m_id = id;
		}
		virtual ~Device(){}

	protected:

		uint32							m_id;
	};

	typedef Device* (*PTR_ALLOC_DEVICE)();
	typedef void (*PTR_FREE_DEVICE)(Device*);

#define FUNC_ALLOC_DEVICE_NAME								"AllocDevice"
#define FUNC_FREE_DEVICE_NAME								"FreeDevice"
}
