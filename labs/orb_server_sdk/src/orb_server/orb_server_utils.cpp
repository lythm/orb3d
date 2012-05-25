#include "orb_server_pch.h"
#include "orb_server_utils.h"
#include "orb_server_ServerApplication.h"

namespace orb
{
	Core* GetCore()
	{
		return Application::Instance()->GetCore();
	}

	void PrintSysMessage(const std::wstring& msg)
	{
		Application::Instance()->PrintSysMessage(msg);
	}
}
