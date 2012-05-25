
#include "LauncherApp.h"



LauncherApp::LauncherApp(void)
{
}


LauncherApp::~LauncherApp(void)
{
}


void LauncherApp::OnUpdate()
{
	if(m_pEngine)
	{
		if(false == m_pEngine->Update())
		{
			ExitApp();
			return;
		}
	}
}
bool LauncherApp::OnInit()
{
	SetTitle(L"Launcher");

	m_pEngine = engine::EngineMainPtr(new engine::EngineMain);

	engine::EngineParameters param;

	param.app_handle = this->m_hWnd;
	param.config_file = "./engine.conf";

	if(m_pEngine->Initialize(param) == false)
	{
		return false;
	}

	return true;
}
void LauncherApp::OnRelease()
{
	if(m_pEngine)
	{
		m_pEngine->Release();
		m_pEngine.reset();
	}
}
