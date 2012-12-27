#pragma once

class CMainFrame;

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
	
	static void									ResizeRenderer(int cx, int cy);
	static RendererPtr							GetRenderer();

	static CMainFrame*							GetMainFrame();
	static engine::RenderSystemPtr				GetRenderSystem();
	static void									UpdateObjectView();
	static void									ClearObjectViewSelection();
	static void									UpdatePropGrid(engine::GameObjectPtr pObj);

	static engine::GameObjectPtr				CreateGameObject(const std::wstring& name);
	static engine::GameObjectComponentPtr		CreateGameObjectComponent(const std::wstring& name);
	static void									OutputInfo(const CString& info);
	static void									OutputBuild(const CString& info);

	static void									UpdateStatusBar_FPS(float fps);

	static ProjectPtr							GetProject();
	static void									SetProject(ProjectPtr pProject);
	static engine::GameObjectPtr				GetSelectedObject();
	static void									SetSelectedObject(engine::GameObjectPtr pObj);
private:

	static int									s_RTWidth;
	static int									s_RTHeight;

	static engine::CoreApiPtr					s_pCore;
	static engine::Sys_GraphicsPtr				s_pSysGraphics;
	static RendererPtr							s_pRenderer;

	static engine::PoolAllocator				s_Allocator;

	static ProjectPtr							s_pProject;

	static engine::GameObjectPtr				s_pSelObject;
};

