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
engine::PoolAllocator				AppContext::s_Allocator;

ProjectPtr							AppContext::s_pProject;
engine::GameObjectPtr				AppContext::s_pSelObject = engine::GameObjectPtr();
PathManagerPtr						AppContext::s_pPathManager;

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
engine::RenderSystemPtr AppContext::GetRenderSystem()
{
	return s_pCore->GetRenderSystem();
}
bool AppContext::InitContext(HWND hwnd, int w, int h)
{
	s_Allocator.Initialize();

	s_RTWidth = w;
	s_RTHeight = h;
	using namespace engine;

	s_pCore = CoreApiPtr(new CoreApi());

	GraphicsSetting setting;
	setting.sysMod = L"./d11graphics.dll";
	setting.backBufferCount = 2;
	setting.depthStencilFormat = G_FORMAT_D24_UNORM_S8_UINT;
	setting.frameBufferFormat = G_FORMAT_R8G8B8A8_UNORM;
	setting.frameBufferHeight = h;
	setting.frameBufferWidth = w;
	setting.multiSampleCount = 1;
	setting.multiSampleQuality = 0;
	setting.windowed = true;
	setting.wnd = hwnd;

#ifdef _DEBUG
	if(false == s_pCore->Initialize(setting))
	{
		return false;
	}
#else
	if(false == s_pCore->Initialize(setting, &s_Allocator))
	{
		return false;
	}
#endif

	s_pCore->GetGameObjectManager()->LoadPackage(L"./extensions/GameEditor_ext.dll");
	s_pCore->GetRenderSystem()->SetClearColor(math::Color4(0.3f, 0.2f, 0.4f, 1.0f));

	s_pRenderer = RendererPtr(new Renderer);
	if(s_pRenderer->Initialize(w, h) == false)
	{
		return false;
	}

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
void AppContext::ResizeRenderer(int cx, int cy)
{
	s_RTWidth = cx;
	s_RTHeight = cy;

	if(s_pRenderer)
	{
		s_pRenderer->Resize(cx, cy);
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
void AppContext::ClearObjectViewSelection()
{
	CMainFrame* pMain = GetMainFrame();
	pMain->GetObjectView()->ClearSelection();
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

	if(pMain == nullptr)
	{
		return;
	}

	pMain->GetPropGrid()->UpdateGameObjectProp(pObj);
}
engine::GameObjectPtr AppContext::CreateGameObject(const std::wstring& name)
{
	using namespace engine;

	GameObjectPtr pObj = GetCoreApi()->CreateGameObject(name);

	GameObjectComponentPtr pPM = CreateGameObjectComponent(L"PropertyManager");

	pObj->AddComponent(pPM);

	pPM = CreateGameObjectComponent(L"DT_Gizmo");
	pObj->AddComponent(pPM);

	return pObj;

}
engine::GameObjectComponentPtr AppContext::CreateGameObjectComponent(const std::wstring& name)
{
	using namespace engine;

	return GetCoreApi()->CreateGameObjectComponent(name);
}
void AppContext::UpdateStatusBar_FPS(float fps)
{
	CMainFrame* pMain = GetMainFrame();
	pMain->SetFPS(fps);
}
ProjectPtr AppContext::GetProject()
{
	return s_pProject;
}
void AppContext::SetProject(ProjectPtr pProject)
{
	s_pProject = pProject;
}
engine::GameObjectPtr AppContext::GetSelectedObject()
{
	return s_pSelObject;
}
void AppContext::SetSelectedObject(engine::GameObjectPtr pObj)
{
	s_pSelObject = pObj;
}