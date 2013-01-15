#pragma once

#include <string>
#include <Windows.h>


namespace ld3d
{
	class WinApp
	{
	public:
		WinApp(void);
		virtual ~WinApp(void);

		bool													Initialize(HINSTANCE hInst, const std::wstring& title, int w, int h);

		void													Release();

		void													Run();
	protected:

		void													SetTitle(const wchar_t* szTitle);
		void													ExitApp();

		virtual void											OnUpdate();
		virtual bool											OnInit();
		virtual void											OnRelease();


		virtual void											HandleMessage(MSG& msg){}

		void													AdjustWindow(int Width, int Height );

		static LRESULT CALLBACK									WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		HWND													GetWnd();

		int														GetClientWidth();
		int														GetClientHeight();

		int														GetWindowWidth();
		int														GetWindowHeight();
	protected:

		HINSTANCE												m_hInst;
		HWND													m_hWnd;

		std::wstring											m_wndClass;
		std::wstring											m_wndTitle;

		int														m_width;
		int														m_height;

		int														m_clientWidth;
		int														m_clientHeight;



	};


}
