#include "StdAfx.h"
#include "AppContext.h"


engine::CoreApiPtr					AppContext::s_pCore;
engine::Sys_GraphicsPtr				AppContext::s_pSysGraphics;
AppContext::AppContext(void)
{
}


AppContext::~AppContext(void)
{
}
engine::CoreApiPtr AppContext::GetCoreApi()
{
	


	return s_pCore;
}
bool AppContext::InitContext(HWND hwnd, int w, int h)
{

	using namespace engine;

	s_pCore = CoreApiPtr(new CoreApi());


	if(false == s_pCore->Initialize(hwnd, w, h))
	{
		return false;
	}

	return true;
}
engine::Sys_GraphicsPtr AppContext::GetSysGraphics()
{
	return s_pCore->GetSysGraphics();
}
void AppContext::ReleaseContext()
{
	s_pCore->Release();
}
void AppContext::UpdateContext()
{
	s_pCore->Update();
}