#pragma once

class CMainFrame;
class CGameEditorApp;

CGameEditorApp*									util_get_app();
CMainFrame*										util_get_main_frame();

void											util_update_object_view(ld3d::GameObjectPtr pObj);
void											util_update_obj_property_grid(ld3d::GameObjectPtr pObj);

void											util_output_info(const CString& info);
void											util_output_build(const CString& build);
void											util_clear_objview_selection();
void											util_update_status_bar_fps(float fps);

void											util_set_rendering_wnd(CWnd* pWnd);
CWnd*											util_get_rendering_wnd();

void											util_update_assets_view();

boost::filesystem::path							util_get_relative_path(boost::filesystem::path const v, boost::filesystem::path const base) ;
bool											util_cpoy_directory(boost::filesystem::path src, boost::filesystem::path dst);