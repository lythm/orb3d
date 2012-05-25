#include "orb_server_pch.h"
#include "orb_server_ServerApplication.h"
#include "orb_server_Core_Impl.h"

#include <vector>

#include <string>
#include <iostream>

namespace orb
{
	Application				Application::s_inst;

	Application* Application::Instance()
	{
		return &s_inst;
	}

	Application::Application(void)
	{
		m_pCore			= NULL;

	}


	Application::~Application(void)
	{
		Release();
	}

	void Application::PrintSysMessage(const std::wstring& msg)
	{
		wprintf(L"#sys: %s\n", msg.c_str());
	}
	bool Application::Initialize()
	{
		Core_Impl* pCore = new Core_Impl;

		m_pCore = pCore;

		if(false == pCore->Initialize())
		{
			m_pCore = NULL;
			return false;

		}

		PrintSysMessage(L"everything is ready.");
		return true;
	}
	void Application::Release()
	{
		if(m_pCore)
		{
			((Core_Impl*)m_pCore)->Release();
			delete (Core_Impl*)m_pCore;
			m_pCore = NULL;
		}
		
	}


	
	void Application::Run()
	{
	
		while(true)
		{
			std::string cmd;

			std::cin >> cmd;

			if(cmd == "quit")
			{
				break;
			}

			if(cmd == "list_sm")
			{
				GetCore()->ListSM();
				continue;
			}
			if(cmd == "list_device")
			{
				GetCore()->ListDevice();
				continue;
			}

			PrintSysMessage(L"unknown command.");
		}
	}

	 
	Core* Application::GetCore()
	{
		return m_pCore;
	}
}

int main(int argc, char* argv[])
{
	using namespace orb;
		
	Application* pApp = Application::Instance();

	if(false == pApp->Initialize())
	{
		return -1;
	}

	pApp->Run();

	pApp->Release();

	
	system("pause");
	return 0;
}

