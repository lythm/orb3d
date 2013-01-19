#include "pch.h"
#include "EngineApp.h"
#include <tchar.h>



namespace ld3d
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

		SysSetting setting;
		setting.graphics.sysMod = L"./d11graphics.dll";
		setting.graphics.backBufferCount = 2;
		setting.graphics.depthStencilFormat = G_FORMAT_D24_UNORM_S8_UINT;
		setting.graphics.frameBufferFormat = G_FORMAT_R8G8B8A8_UNORM;
		setting.graphics.frameBufferHeight = GetClientHeight();
		setting.graphics.frameBufferWidth = GetClientWidth();
		setting.graphics.multiSampleCount = 1;
		setting.graphics.multiSampleQuality = 0;
		setting.graphics.windowed = true;
		setting.graphics.wnd = GetWnd();

		setting.input.sysMod = L"";
		setting.input.wnd = GetWnd();

		setting.sound.maxChannels = 100;
		setting.sound.sysMod = L"./fmod_sound.dll";

		setting.physics.sysMod = L"";

		if(false == m_pCore->Initialize(setting))
		{
			return false;
		}
		
		m_pGameManager = m_pCore->GetAllocator()->AllocObject<GameManager>();

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

			float fps = float(frames * 1000) / float(dt);
			swprintf(buffer, 100, L"fps : %.3f - %fms", fps, 1000.0f / fps);

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

	using namespace ld3d;
	EngineApp app;

	if(false == app.Initialize(hInstance, L"Main Window", 800, 600))
	{
		return -1;
	}
	app.Run();

	app.Release();

	return 0;
}
