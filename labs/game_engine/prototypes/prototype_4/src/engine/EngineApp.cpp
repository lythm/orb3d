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
		
		//Sleep(1);

	}
	bool EngineApp::OnInit()
	{

		m_pCore = CoreApiPtr(new CoreApi);

		GraphicsSetting setting;
		setting.sysMod = L"./d3d11graphics.dll";
		setting.backBufferCount = 2;
		setting.depthStencilFormat = G_FORMAT_D32_FLOAT;
		setting.frameBufferFormat = G_FORMAT_R8G8B8A8_UNORM;
		setting.frameBufferHeight = GetClientHeight();
		setting.frameBufferWidth = GetClientWidth();
		setting.multiSampleCount = 1;
		setting.multiSampleQuality = 0;
		setting.windowed = true;
		setting.wnd = GetWnd();

		if(false == m_pCore->Initialize(setting))
		{
			return false;
		}
		
		m_pGameManager = m_pCore->AllocObject<GameManager>();

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

		int iv = 100;
		if(dt >= iv)
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

	if(false == app.Initialize(hInstance, L"Main Window", 800, 600))
	{
		return -1;
	}
	app.Run();

	app.Release();

	return 0;
}
