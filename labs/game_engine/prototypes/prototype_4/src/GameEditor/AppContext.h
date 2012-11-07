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
private:

	static engine::CoreApiPtr					s_pCore;
	static engine::Sys_GraphicsPtr				s_pSysGraphics;
};

