#pragma once

#include <string>
#include <Windows.h>

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

	void													AdjustWindow(int Width, int Height );

	static LRESULT CALLBACK									WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
protected:

	HINSTANCE												m_hInst;
	HWND													m_hWnd;

	std::wstring											m_wndClass;
	std::wstring											m_wndTitle;

	int														m_width;
	int														m_height;

	

};

