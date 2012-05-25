#pragma once

#include <string>
#include <engine.h>

class WinApp
{
public:
	WinApp(void);
	virtual ~WinApp(void);

	bool													Initialize(HINSTANCE hInst, const std::wstring& title, int w, int h);

	void													Release();

	void													Run();
private:

	void													Update();

	void													AdjustWindow(int Width, int Height );

	static LRESULT CALLBACK									WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:

	HINSTANCE												m_hInst;
	HWND													m_hWnd;

	std::wstring											m_wndClass;
	std::wstring											m_wndTitle;

	int														m_width;
	int														m_height;

	boost::shared_ptr<engine::EngineCore>					m_pEngine;

};

