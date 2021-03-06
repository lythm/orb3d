#include "winapp.h"
#include <tchar.h>


WinApp::WinApp(void)
{
	m_hInst	= NULL;
	m_hWnd = NULL;
	m_width = 640;
	m_height = 480;
}


WinApp::~WinApp(void)
{
}


bool WinApp::Initialize(HINSTANCE hInst, const std::wstring& title, int w, int h)
{
	m_hInst = hInst;
	m_wndTitle = title;
	m_wndClass = title + L"_WndClass";

	m_width = w;
	m_height = h;

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= m_hInst;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= m_wndClass.c_str();
	wcex.hIconSm		= NULL;


	if(FALSE == RegisterClassEx(&wcex))
	{
		return false;
	}


	m_hWnd = CreateWindow(m_wndClass.c_str(), 
		m_wndTitle.c_str(), 
		(WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU), 
		CW_USEDEFAULT, 
		0, 
		m_width, 
		m_height, 
		NULL, 
		NULL, 
		m_hInst, 
		NULL);

	if (!m_hWnd)
	{
		return false;
	}

	AdjustWindow(m_width, m_height);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	if(OnInit() == false)
	{
		return false;
	}
	
	return true;
}
void WinApp::AdjustWindow(int Width, int Height )
{
	RECT WinRect;
	RECT ClientRect;

	GetWindowRect( m_hWnd, &WinRect );
	GetClientRect( m_hWnd, &ClientRect );

	int ClientWidth  = ClientRect.right  - ClientRect.left;
	int ClientHeight = ClientRect.bottom - ClientRect.top;

	int IncX = Width  - ClientWidth;
	int IncY = Height - ClientHeight;

	SetWindowPos( m_hWnd, 0, WinRect.left, WinRect.top, WinRect.right - WinRect.left + IncX, WinRect.bottom - WinRect.top + IncY, SWP_NOZORDER );
}
void WinApp::Release()
{

	OnRelease();
}
LRESULT CALLBACK WinApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CHAR:
		{
			wchar_t buffer[2];
			buffer[1] = 0;
			buffer[0] = wParam;
			OutputDebugString(buffer);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void WinApp::Run()
{
	MSG msg = {0};
	while( WM_QUIT != msg.message )
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{

			OnUpdate();
		}
	}

	return;
}
void WinApp::OnUpdate()
{

}

bool WinApp::OnInit()
{
	return true;
}

void WinApp::OnRelease()
{
}



void WinApp::SetTitle(const wchar_t* szTitle)
{
	SetWindowText(m_hWnd, szTitle);
}
void WinApp::ExitApp()
{
	PostQuitMessage(0);
}
