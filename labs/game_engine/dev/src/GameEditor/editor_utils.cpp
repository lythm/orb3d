#include "stdafx.h"
#include "editor_utils.h"
#include "MainFrm.h"


static CWnd*						g_pRenderWnd				= nullptr;

CGameEditorApp* util_get_app()
{
	return (CGameEditorApp*)AfxGetApp();
}
CMainFrame* util_get_main_frame()
{
	return (CMainFrame*)AfxGetApp()->GetMainWnd();
}
void util_update_object_view(engine::GameObjectPtr pObj)
{
	util_get_main_frame()->UpdateObjectView(pObj);
}
void util_update_obj_property_grid(engine::GameObjectPtr pObj)
{
	util_get_main_frame()->UpdatePropGrid(pObj);
}
void util_output_info(const CString& info)
{
	util_get_main_frame()->OutputInfo(info);
}
void util_output_build(const CString& build)
{
	util_get_main_frame()->OutputInfo(build);
}
void util_clear_objview_selection()
{
	CMainFrame* pMain = util_get_main_frame();
	pMain->GetObjectView()->ClearSelection();
}
void util_update_status_bar_fps(float fps)
{
	CMainFrame* pMain = util_get_main_frame();
	pMain->SetFPS(fps);
}
void util_set_rendering_wnd(CWnd* pWnd)
{
	g_pRenderWnd = pWnd;
}
CWnd*  util_get_rendering_wnd()
{
	return g_pRenderWnd;
}

void util_update_assets_view()
{
	CMainFrame* pMain = util_get_main_frame();
	pMain->UpdateAssetsView();
}