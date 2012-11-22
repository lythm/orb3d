#pragma once


class AppContext
{
public:
	AppContext(void);
	virtual ~AppContext(void);


	static bool									InitContext(HWND hwnd, int w, int h);
	static void									UpdateContext();
	static void									ReleaseContext();
	static engine::CoreApiPtr					GetCoreApi();
	static engine::Sys_GraphicsPtr				GetSysGraphics();

	static int									GetRTViewWidth();
	static int									GetRTViewHeight();
	static void									ResizeRTView(int cx, int cy);

	static RendererPtr							GetRenderer();
private:

	static int									s_RTWidth;
	static int									s_RTHeight;

	static engine::CoreApiPtr					s_pCore;
	static engine::Sys_GraphicsPtr				s_pSysGraphics;
	static RendererPtr							s_pRenderer;
};

