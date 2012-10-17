#include "pch.h"
#include "EngineApp.h"
#include <tchar.h>
#include "WMInput.h"


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

		//SetTitle(buffer);


		m_pObjectManager->UpdateObjects();


		ShowFPS();

		m_pSysGraphics->ClearRenderTarget();

	
		m_pSysGraphics->SetIndexBuffer(m_pIB);
		m_pSysGraphics->SetVertexBuffer(m_pVB);
		m_pSysGraphics->SetPrimitiveType(Sys_Graphics::PT_TRIANGLE_LIST);
		
		m_pGFX->ApplyVertexFormat();

		while(m_pGFX->BeginPass())
		{
			m_pGFX->ApplyPass();

			m_pSysGraphics->DrawPrimitive(3, 0, 0);

			m_pGFX->EndPass();

		}

		m_pSysGraphics->Present();

		Sleep(1);

	}
	bool EngineApp::OnInit()
	{

		m_pSysManager = SysManagerPtr(new SysManager);

		//m_pSysInput = m_pSysManager->LoadSysInput(L"./d8input.dll");

		m_pWMInput = boost::shared_ptr<WMInput>(new WMInput);

		m_pSysInput	= m_pWMInput;

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

		m_pSysGraphics->SetClearColor(math::Color4(0.0, 0.0, 0.0, 1.0));
		
		m_pObjectManager = GameObjectManagerPtr(new engine::GameObjectManager);


		struct Vertex
		{
			math::Vector3 pos;
		};

		Vertex verts[] = 
		{
			math::Vector3(100, 0, 0),
			math::Vector3(0, 100, 0),
			math::Vector3(0, 0, 0),
		};


		m_pVB = m_pSysGraphics->CreateBuffer(Sys_Graphics::BT_VERTEX_BUFFER, sizeof(math::Vector3) * 3, verts, true);

		short indice[] = {0, 1, 2,};

		m_pIB = m_pSysGraphics->CreateBuffer(Sys_Graphics::BT_INDEX_BUFFER, sizeof(short) * 3, indice, true);


		m_pGFX = m_pSysGraphics->CreateGFXFromFile("./assets/gfx/test.cgfx");

		VertexElement vf[] = 
		{
			VertexElement(0, VertexElement::POSITION,VertexElement::VE_FLOAT3),
		};

		m_pGFX->SetVertexFormat(vf, 1);
		
		math::Matrix44 view = math::MatrixLookAtLH(math::Vector3(0, 0, -10), math::Vector3(0, 0, 0), math::Vector3(0, 1, 0));
		math::Matrix44 proj = math::MatrixPerspectiveFovLH(3.0f/4.0f * 3.14, 4.0f/ 3.0f, 0.0001, 10000);

		m_pGFX->SetMatrixBySemantic("WORLDVIEWPROJ", view * proj);
		return true;
	}
	void EngineApp::OnRelease()
	{

		m_pIB->Release();
		m_pVB->Release();
		m_pGFX->Release();


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

	void EngineApp::HandleMessage(MSG& msg)
	{
		if(m_pWMInput)
		{
			m_pWMInput->ProcessMessage(msg);
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
