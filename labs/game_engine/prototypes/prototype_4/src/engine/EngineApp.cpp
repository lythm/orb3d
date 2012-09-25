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
		m_pSysInput->Update();


		if(m_pSysInput->GetKeyState().KeyDown(Sys_Input::key_h))
		{
			//OutputDebugString(L"key down\n");
		}

		Sys_Input::MouseState ms = m_pSysInput->GetMouseState();

		wchar_t buffer[1024];

		wsprintf(buffer, L"X:%d,Y:%d", ms.x, ms.y);

		//OutputDebugString(buffer);

	//	SetTitle(buffer);


		m_pObjectManager->UpdateObjects();


		ShowFPS();

		m_pSysGraphics->ClearRenderTarget();

	//	Sleep(1000);
		m_pSysGraphics->Present();

	}
	bool EngineApp::OnInit()
	{

		m_pSysManager = SysManagerPtr(new SysManager);

		m_pSysInput = m_pSysManager->LoadSysInput(L"./d8input.dll");

		if(m_pSysInput == Sys_InputPtr())
		{
			return false;
		}

		if(false == m_pSysInput->Initialize(GetWnd()))
		{
			return false;
		}

		m_pSysGraphics = m_pSysManager->LoadSysGraphics(L"./d11graphics.dll");

		if(m_pSysGraphics == Sys_GraphicsPtr())
		{
			return false;
		}
		if(false == m_pSysGraphics->Initialize(GetWnd(), GetClientWidth(), GetClientHeight()))
		{
			return false;
		}

		m_pSysGraphics->SetClearColor(math::Color4(0.5, 0.5, 0, 1.0));
		
		m_pObjectManager = GameObjectManagerPtr(new engine::GameObjectManager);

		return true;
	}
	void EngineApp::OnRelease()
	{

		m_pObjectManager->ReleaseAllObject();
		m_pObjectManager.reset();
		
		m_pSysGraphics->Release();
		m_pSysGraphics.reset();

		m_pSysInput->Release();
		m_pSysInput.reset();
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
