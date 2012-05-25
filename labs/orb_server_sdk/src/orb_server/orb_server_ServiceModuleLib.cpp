#include "orb_server_pch.h"
#include "orb_server_ServiceModuleLib.h"

namespace orb
{
	ServiceModuleLib::ServiceModuleLib(void)
	{
		m_lib						= invalid_kernel_object;
		m_libname					= L"";

	}


	ServiceModuleLib::~ServiceModuleLib(void)
	{
	}

}
