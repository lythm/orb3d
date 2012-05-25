#pragma once

#include "ede/ede_event.h"

namespace orb
{
	namespace ede
	{
		struct Event;
	};
	class ServiceMod;
	
	class Core
	{
	public:

		virtual const std::vector<std::wstring>&	AppSettings(const std::wstring& key)						= 0;
		virtual std::wstring						AppSettings(const std::wstring& key, int index)				= 0;
		virtual bool								InstallServiceMod(ServiceMod* pMod)							= 0;
		virtual void								UnInstallServiceMod(ServiceMod* pMod)						= 0;

		virtual void*								MemAlloc(uint32 bytes)										= 0;
		virtual void								MemFree(void* mem)											= 0;

		virtual void								ListSM()													= 0;
		virtual void								ListDevice()												= 0;



	protected:
		Core(){}
		virtual ~Core(){}

	};
};
