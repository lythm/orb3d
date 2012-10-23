#include "pch.h"
#include "EngineApp.h"
#include <tchar.h>



namespace engine
{

	EngineApp::EngineApp(void)
	{
	}


	EngineApp::~EngineApp(void)
	{
	}
	void EngineApp::OnUpdate()
	{
		m_pCore->Update();

		ShowFPS();


		


		m_pGameManager->GetGame()->Update();


		Sleep(1);

	}
	bool EngineApp::OnInit()
	{

		m_pCore = CoreApiPtr(new CoreApi);

		if(false == m_pCore->Initialize(GetWnd(), GetClientWidth(), GetClientHeight()))
		{
			return false;
		}

		


		m_pGameManager = GameManagerPtr(new GameManager);

		if(false == m_pGameManager->Initialize(L"./game.dll"))
		{
			return false;
		}

		if(false == m_pGameManager->GetGame()->Initialize(m_pCore))
		{
			return false;
		}

		return true;
	}
	void EngineApp::OnRelease()
	{
		if(m_pGameManager)
		{
			m_pGameManager->GetGame()->Release();
			m_pGameManager->Release();
			m_pGameManager.reset();
		}
		
		if(m_pCore)
		{
			m_pCore->Release();
			m_pCore.reset();
		}
	}

	void EngineApp::ShowFPS()
	{
		static int tick = GetTickCount();

		static int frames = 0;
		int dt = GetTickCount() - tick;

		if(dt >= 1000)
		{

			wchar_t buffer[100];

			swprintf(buffer, L"fps : %.3f", float(frames * 1000) / float(dt));

			SetTitle(buffer);

			tick = GetTickCount();
			frames = 0;
		}

		frames ++;
	}

	void EngineApp::HandleMessage(MSG& msg)
	{
		if(m_pCore)
		{
			m_pCore->HandleMessage(msg);
		}
	}

}






int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	using namespace engine;
	EngineApp app;

	if(false == app.Initialize(hInstance, L"Main Window", 1024, 768))
	{
		return -1;
	}
	app.Run();

	app.Release();

	return 0;
}
