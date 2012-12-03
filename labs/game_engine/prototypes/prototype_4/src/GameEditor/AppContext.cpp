#include "StdAfx.h"
#include "AppContext.h"
#include "Renderer.h"
#include "MainFrm.h"
#include "Project.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"


engine::CoreApiPtr					AppContext::s_pCore;
engine::Sys_GraphicsPtr				AppContext::s_pSysGraphics;
RendererPtr							AppContext::s_pRenderer;

int									AppContext::s_RTWidth	= 0;
int									AppContext::s_RTHeight	= 0;
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
	s_RTWidth = w;
	s_RTHeight = h;
	using namespace engine;

	s_pCore = CoreApiPtr(new CoreApi());

	if(false == s_pCore->Initialize(hwnd, w, h, G_FORMAT_R8G8B8A8_UNORM))
	{
		return false;
	}
	OutputInfo(L"Engine Initialized.");

	s_pRenderer = RendererPtr(new Renderer);
	if(s_pRenderer->Initialize(w, h) == false)
	{
		return false;
	}

	OutputInfo(L"Renderer Initialized.");
	return true;
}
engine::Sys_GraphicsPtr AppContext::GetSysGraphics()
{
	if(s_pCore == NULL)
	{
		return engine::Sys_GraphicsPtr();
	}
	return s_pCore->GetSysGraphics();
}
void AppContext::ReleaseContext()
{
	if(s_pRenderer)
	{
		s_pRenderer->Release();
		s_pRenderer.reset();
	}

	if(s_pCore != NULL)
	{
		s_pCore->Release();
		s_pCore.reset();
	}
}
void AppContext::UpdateContext()
{
	if(s_pCore)
	{
		s_pCore->Update();
	}
}
int AppContext::GetRTViewWidth()
{
	return s_RTWidth;
}
int AppContext::GetRTViewHeight()
{
	return s_RTHeight;
}
void AppContext::ResizeRTView(int cx, int cy)
{
	s_RTWidth = cx;
	s_RTHeight = cy;

	if(s_pRenderer)
	{
		s_pRenderer->ResetViewPort(cx, cy);
	}
}
RendererPtr AppContext::GetRenderer()
{
	return s_pRenderer;
}
CMainFrame* AppContext::GetMainFrame()
{
	return (CMainFrame*)AfxGetMainWnd();
}
void AppContext::UpdateObjectView()
{
	CMainFrame* pMain = GetMainFrame();
	pMain->GetObjectView()->UpdateObjectView();
}

void AppContext::OutputInfo(const CString& info)
{
	CMainFrame* pMain = GetMainFrame();
	pMain->GetOutput()->OuputInfo(info);
}
void AppContext::OutputBuild(const CString& info)
{
	CMainFrame* pMain = GetMainFrame();
	pMain->GetOutput()->OuputBuild(info);
}
void AppContext::UpdatePropGrid(engine::GameObjectPtr pObj)
{
	CMainFrame* pMain = GetMainFrame();
	pMain->GetPropGrid()->UpdateGameObjectProp(pObj);
}