#include "stdafx.h"
#include "editor_utils.h"
#include "MainFrm.h"


static CWnd*						g_pRenderWnd				= nullptr;
static CMainFrame*					g_pMainFrame				= nullptr;

CGameEditorApp* util_get_app()
{
	return (CGameEditorApp*)AfxGetApp();
}
CMainFrame* util_get_main_frame()
{
	return g_pMainFrame;
}
void util_set_main_frame(CMainFrame* pWnd)
{
	g_pMainFrame = pWnd;
}
void util_update_object_view(ld3d::GameObjectPtr pObj)
{
	if(util_get_main_frame())
	{
		util_get_main_frame()->UpdateObjectView(pObj);
	}
}
void util_update_obj_property_grid(ld3d::GameObjectPtr pObj)
{
	if(util_get_main_frame())
	{
		util_get_main_frame()->UpdatePropGrid(pObj);
	}
}

void util_clear_objview_selection()
{
	CMainFrame* pMain = util_get_main_frame();
	
	if(pMain)
	{
		pMain->GetObjectView()->ClearSelection();
	}
}
void util_update_status_bar_fps(float fps)
{
	CMainFrame* pMain = util_get_main_frame();
	if(pMain)
	{
		pMain->SetFPS(fps);
	}
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
	if(pMain)
	{
		pMain->UpdateAssetsView();
	}
}



boost::filesystem::path util_get_relative_path(boost::filesystem::path const v, boost::filesystem::path const base) 
{
  // create absolute paths

	namespace fs = boost::filesystem;

    fs::path p = fs::absolute(v);

    fs::path r = fs::absolute(base);

    // if root paths are different, return absolute path
    if( p.root_path() != r.root_path() )
        return p;

    // initialize relative path
    fs::path result;

    // find out where the two paths diverge
    fs::path::const_iterator itr_path = p.begin();
    fs::path::const_iterator itr_relative_to = r.begin();
    while( *itr_path == *itr_relative_to && itr_path != p.end() && itr_relative_to != r.end() )
	{
        ++itr_path;
        ++itr_relative_to;
    }

    // add "../" for each remaining token in relative_to
    if( itr_relative_to != r.end() )
	{
        ++itr_relative_to;
        while( itr_relative_to != r.end() ) 
		{
            result /= "..";
            ++itr_relative_to;
        }
    }

    // add remaining path
    while( itr_path != p.end() ) 
	{
        result /= *itr_path;
        ++itr_path;
    }

    return result;
}

bool util_cpoy_directory(boost::filesystem::path src, boost::filesystem::path dst)
{
	namespace fs = boost::filesystem;
	try
	{
		// Check whether the function call is valid
		if( !fs::exists(src) || !fs::is_directory(src))
		{
			return false;
		}
		if(fs::exists(dst))
		{
			return false;
		}
		// Create the destination directory
		if(!fs::create_directory(dst))
		{
			return false;
		}
	}
	catch(fs::filesystem_error const & e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}
	// Iterate through the source directory
	for(fs::directory_iterator file(src); file != fs::directory_iterator(); ++file)
	{
		try
		{
			fs::path current(file->path());
			if(fs::is_directory(current))
			{
				// Found directory: Recursion
				if(!util_cpoy_directory(current, dst / current.filename()))
				{
					return false;
				}
			}
			else
			{
				// Found file: Copy
				fs::copy_file(current, dst / current.filename());
			}
		}
		catch(fs::filesystem_error const & e)
		{
			std:: cerr << e.what() << std::endl;
		}
	}
	return true;
}
void util_log_info(const std::wstring& text)
{
	if(util_get_main_frame())
	{
		util_get_main_frame()->OutputInfo(text.c_str());
	}
}
void util_log_build(const std::wstring& text)
{
	if(util_get_main_frame())
	{
		util_get_main_frame()->outputBuild(text.c_str());
	}
}