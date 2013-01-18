
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "GameEditor.h"

#include "AppSettingsDlg.h"

#include "MainFrm.h"
#include "Renderer.h"


#include "MeshImporter_3DSMax.h"
#include "Project.h"

#include "RenderingSettingDlg.h"

#include "PreviewWnd.h"
#include "editor_utils.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

	const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_COMPONENT_MENU_BASE, ID_COMPONENT_MENU_BASE + 1000, &CMainFrame::OnComponentMenu)
	ON_UPDATE_COMMAND_UI_RANGE(ID_COMPONENT_MENU_BASE, ID_COMPONENT_MENU_BASE + 1000, &CMainFrame::OnUpdateComponentMenuUI)
	ON_COMMAND_RANGE(ID_COMPONENT_MENU_BASE + 1000, ID_COMPONENT_MENU_BASE + 2000, &CMainFrame::OnCreateFromTemplateMenu)
	ON_UPDATE_COMMAND_UI_RANGE(ID_COMPONENT_MENU_BASE + 1000, ID_COMPONENT_MENU_BASE + 2000, &CMainFrame::OnUpdateCreateFromTemplateMenuUI)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)

	ON_COMMAND(ID_VIEW_CAPTION_BAR, &CMainFrame::OnViewCaptionBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CAPTION_BAR, &CMainFrame::OnUpdateViewCaptionBar)
	ON_COMMAND(ID_TOOLS_OPTIONS, &CMainFrame::OnOptions)
	ON_WM_SETTINGCHANGE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_GAMEOBJECT_CREATEEMPTY, &CMainFrame::OnGameobjectCreateempty)
	ON_COMMAND(ID_VIEW_SHOWGRID, &CMainFrame::OnViewShowgrid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHOWGRID, &CMainFrame::OnUpdateViewShowgrid)
	ON_COMMAND(ID_EDIT_APPSETTINGS, &CMainFrame::OnEditAppsettings)
	ON_COMMAND(ID_IMPORT_IMPORTMAXMESH, &CMainFrame::OnImportImportmaxmesh)
	ON_COMMAND(ID_RENDERING_SETTING, &CMainFrame::OnRenderingSetting)
	ON_COMMAND(ID_BUILD_PREVIEW, &CMainFrame::OnBuildPreview)
	ON_COMMAND(ID_FILE_NEW, &CMainFrame::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CMainFrame::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CMainFrame::OnFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE_SCENE, &CMainFrame::OnFileSaveScene)
	ON_COMMAND(ID_FILE_OPEN_SCENE, &CMainFrame::OnFileOpenScene)
	ON_COMMAND(ID_FILE_SAVE_SCENE_AS, &CMainFrame::OnFileSaveSceneAs)
	ON_COMMAND(ID_FILE_NEW_SCENE, &CMainFrame::OnFileNewScene)
	ON_COMMAND(ID_FILE_NEW_PROJECT, &CMainFrame::OnFileNewProject)
	ON_COMMAND(ID_FILE_OPEN_PROJECT, &CMainFrame::OnFileOpenProject)
	ON_COMMAND(ID_FILE_SAVE_PROJECT, &CMainFrame::OnFileSaveProject)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
}

CMainFrame::~CMainFrame()
{

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("未能创建菜单栏\n");
		return -1;      // 未能创建
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// 防止菜单栏在激活时获得焦点
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// 允许用户定义的工具栏操作:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	m_wndStatusBar.SetPaneWidth(1, 60);

	// TODO: 如果您不希望工具栏和菜单栏可停靠，请删除这五行
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 创建标题栏:
	if (!CreateCaptionBar())
	{
		TRACE0("未能创建标题栏\n");
		return -1;      // 未能创建
	}

	// 加载菜单项图像(不在任何标准工具栏上):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// 创建停靠窗口
	if (!CreateDockingWindows())
	{
		TRACE0("未能创建停靠窗口\n");
		return -1;
	}

	m_wndTplView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndObjectView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndFileView);
	CDockablePane* pTabbedBar = NULL;
	m_wndObjectView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);

	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	
	DockPane(&m_wndOutput);
	
	
	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);
	
	m_wndInspectorView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndInspectorView);
	
	m_wndTplView.AttachToTabWnd(&m_wndProperties, DM_SHOW, TRUE, &pTabbedBar);

	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	// 启用工具栏和停靠窗口菜单替换
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// 启用快速(按住 Alt 拖动)工具栏自定义
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// 加载用户定义的工具栏图像
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// 启用菜单个性化(最近使用的命令)
	// TODO: 定义您自己的基本命令，确保每个下拉菜单至少有一个基本命令。
	/*CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);
	lstBasicCommands.AddTail(ID_SORTING_SORTALPHABETIC);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYTYPE);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYACCESS);
	lstBasicCommands.AddTail(ID_SORTING_GROUPBYTYPE);*/

	//	lstBasicCommands.AddTail(ID_GAMEOBJECT_CREATEEMPTY);

	//CMFCToolBar::SetBasicCommands(lstBasicCommands);


	util_set_main_frame(this);

	UpdateComClassMap();

	UpdateTemplateMap();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// 创建类视图
	CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndObjectView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_OBJECTVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“类视图”窗口\n");
		return FALSE; // 未能创建
	}

	// 创建文件视图
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“文件视图”窗口\n");
		return FALSE; // 未能创建
	}

	// Inspector View
	if (!m_wndInspectorView.Create(L"Inspector", this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_INSPECTOR, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT| CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“Inspector View”窗口\n");
		return FALSE; // 未能创建
	}



	// 创建模板视图
	CString strTplView = L"模板窗口";

	ASSERT(bNameValid);
	if (!m_wndTplView.Create(strTplView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_TPLVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“模板视图”窗口\n");
		return FALSE; // 未能创建
	}


	// 创建输出窗口
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建输出窗口\n");
		return FALSE; // 未能创建
	}

	// 创建属性窗口
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“属性”窗口\n");
		return FALSE; // 未能创建
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndFileView.SetIcon(hFileViewIcon, FALSE);

	HICON hObjectViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndObjectView.SetIcon(hObjectViewIcon, FALSE);

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

	HICON hInspectorBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndInspectorView.SetIcon(hPropertiesBarIcon, FALSE);

	HICON hTemplateViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndTplView.SetIcon(hTemplateViewIcon, FALSE);



}

BOOL CMainFrame::CreateCaptionBar()
{
	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE))
	{
		TRACE0("未能创建标题栏\n");
		return FALSE;
	}

	BOOL bNameValid;

	CString strTemp, strTemp2;
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_LEFT, FALSE);
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButtonToolTip(strTemp);

	bNameValid = strTemp.LoadString(IDS_CAPTION_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_LEFT);

	m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_LEFT);
	bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TIP);
	ASSERT(bNameValid);
	bNameValid = strTemp2.LoadString(IDS_CAPTION_IMAGE_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetImageToolTip(strTemp, strTemp2);

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 扫描菜单*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	m_wndOutput.UpdateFonts();
	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnViewCaptionBar()
{
	m_wndCaptionBar.ShowWindow(m_wndCaptionBar.IsVisible() ? SW_HIDE : SW_SHOW);
	RecalcLayout(FALSE);
}

void CMainFrame::OnUpdateViewCaptionBar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndCaptionBar.IsVisible());
}

void CMainFrame::OnOptions()
{
}


BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// 基类将执行真正的工作

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// 为所有用户工具栏启用自定义按钮
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}


void CMainFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	UpdatePropGrid(ld3d::GameObjectPtr());
	UpdateObjectView(ld3d::GameObjectPtr());

	ProjectPtr pProject = Project::Instance();
	pProject->Close();
		
	CFrameWndEx::OnClose();
}
CObjectView* CMainFrame::GetObjectView()
{
	return &m_wndObjectView;
}
COutputWnd* CMainFrame::GetOutput()
{
	return &m_wndOutput;
}
CPropertiesWnd*	CMainFrame::GetPropGrid()
{
	return &m_wndProperties;
}

void CMainFrame::OnGameobjectCreateempty()
{
	Project::Instance()->CreateObject_Empty();

	UpdateObjectView(Project::Instance()->Root());

	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnViewShowgrid()
{
	bool bShow = Project::Instance()->ShowingGrid();

	Project::Instance()->ShowGrid(!bShow);
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnUpdateViewShowgrid(CCmdUI *pCmdUI)
{
	bool bShow = Project::Instance()->ShowingGrid();
	pCmdUI->SetCheck(bShow);
}


void CMainFrame::OnEditAppsettings()
{

	CAppSettingsDlg dlg(this);

	dlg.DoModal();
}
class Test
{
public:
	void		foo(ld3d::EventPtr pEvent)
	{
	}
};
void CMainFrame::OnImportImportmaxmesh()
{
}


void CMainFrame::SetFPS(float fps)
{
	CString str;
	str.Format(L"FPS: %.1f", fps);
	m_wndStatusBar.SetPaneText(1, str);

}

bool CMainFrame::UpdateComponentMenu(CMFCPopupMenu* pMenu)
{
	if(pMenu == nullptr)
	{
		return false;
	}

	CString str;
	CMFCToolBarMenuButton* pParent = pMenu->GetParentButton();

	if(pParent == nullptr)
	{
		return false;
	}
	if(pParent->m_strText != L"Component")
	{
		return false;
	}

	using namespace ld3d;

	UpdateComClassMap();

	boost::unordered_map<std::wstring, std::vector<ExtPackage::ComponentClass*> >::iterator it = m_ComClassMap.begin();

	pMenu->RemoveAllItems();

	int id = ID_COMPONENT_MENU_BASE + 1;
	for(it; it != m_ComClassMap.end(); ++it)
	{
		if(it->second.size() == 0)
		{
			continue;
		}
		CMenu m;
		m.CreateMenu();
		for(size_t i = 0; i < it->second.size(); ++i)
		{
			m.InsertMenuW(i, MF_BYPOSITION, id, it->second[i]->m_name.c_str());

			id++;
		}

		CMFCToolBarMenuButton b(-1, m.GetSafeHmenu(), -1, it->first.c_str());
		m.Detach();

		pMenu->InsertItem(b);
	}

	return true;
}
bool CMainFrame::UpdateTemplateMenu(CMFCPopupMenu* pMenu)
{
	if(pMenu == nullptr)
	{
		return false;
	}

	CString str;
	CMFCToolBarMenuButton* pParent = pMenu->GetParentButton();

	if(pParent == nullptr)
	{
		return false;
	}
	if(pParent->m_strText != L"GameObject")
	{
		return false;
	}


	UpdateTemplateMap();
	using namespace ld3d;

	boost::unordered_map<std::wstring, std::vector<ld3d::GameObjectTemplate*> >::iterator it = m_templateMap.begin();

	pMenu->RemoveAllItems();

	CMFCToolBarMenuButton b(ID_GAMEOBJECT_CREATEEMPTY, nullptr, -1, L"Empty");

	pMenu->InsertItem(b);
	pMenu->InsertSeparator();

	int id = ID_COMPONENT_MENU_BASE + 1001;
	for(it; it != m_templateMap.end(); ++it)
	{
		if(it->second.size() == 0)
		{
			continue;
		}
		CMenu m;
		
		m.CreateMenu();
		for(size_t i = 0; i < it->second.size(); ++i)
		{
			m.InsertMenuW(i, MF_BYPOSITION, id, it->second[i]->GetName().c_str());

			id++;
		}

		CMFCToolBarMenuButton b(-1, m.GetSafeHmenu(), -1, it->first.c_str());
		m.Detach();

		pMenu->InsertItem(b);
	}

	return true;
}
ld3d::GameObjectTemplate* CMainFrame::FindTemplateByMenuID(UINT uID)
{

	using namespace ld3d;

	boost::unordered_map<std::wstring, std::vector<ld3d::GameObjectTemplate*> >::iterator it = m_templateMap.begin();

	int id = ID_COMPONENT_MENU_BASE + 1001;
	for(it; it != m_templateMap.end(); ++it)
	{
		if(it->second.size() == 0)
		{
			continue;
		}
		for(size_t i = 0; i < it->second.size(); ++i)
		{
			if(id == uID)
			{
				return it->second[i];
			}

			id++;
		}

	}

	return nullptr;
}

BOOL CMainFrame::OnShowPopupMenu(CMFCPopupMenu* pMenuPopup)
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateComponentMenu(pMenuPopup);
	UpdateTemplateMenu(pMenuPopup);

	return CFrameWndEx::OnShowPopupMenu(pMenuPopup);
}


void CMainFrame::OnUpdateFrameMenu(HMENU hMenuAlt)
{
	// TODO: 在此添加专用代码和/或调用基类

	CFrameWndEx::OnUpdateFrameMenu(hMenuAlt);
}


BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CFrameWndEx::OnCommand(wParam, lParam);
}


BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CFrameWndEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
void CMainFrame::OnComponentMenu(UINT nID)
{
	using namespace ld3d;
	ExtPackage::ComponentClass* pClass = FindClassByMenuID(nID);

	GameObjectPtr pObj = Project::Instance()->GetSelObject();

	if(pClass->m_bExclusive && pObj->GetComponent(pClass->m_name) != GameObjectComponentPtr())
	{
		CString str = pClass->m_name.c_str() + CString(L" can only be added once per object");
		MessageBox(str, L"Component Error", MB_ICONERROR);
		return;
	}

	GameObjectComponentPtr pCom = Project::Instance()->CreateGameObjectComponent(pClass->m_name);

	pObj->AddComponent(pCom);

	UpdatePropGrid(pObj);
	return;
}
void CMainFrame::OnCreateFromTemplateMenu(UINT nID)
{
	using namespace ld3d;

	GameObjectTemplate* pTpl = FindTemplateByMenuID(nID);

	GameObjectPtr pObj = Project::Instance()->CreateObjectFromTpl(pTpl->GetName(), pTpl->GetName());

	UpdateObjectView(Project::Instance()->Root());
	UpdatePropGrid(pObj);

	return;
}
bool CMainFrame::UpdateTemplateMap()
{
	using namespace ld3d;

	m_templateMap.clear();

	ld3d::CoreApiPtr pCore = Project::Instance()->GetCoreApi();
	if(pCore == nullptr)
	{
		return false;
	}

	GameObjectManagerPtr pManager = pCore->GetGameObjectManager();

	for(size_t i = 0; i < pManager->GetPackageCount(); ++i)
	{
		ExtPackage* pPack = pManager->GetPackageByIndex(i);
		for(size_t ii = 0; ii < pPack->GetTemplateCount(); ++ii)
		{
			GameObjectTemplate* pTpl = pPack->GetTemplateByIndex(ii);

			m_templateMap[pTpl->GetCataLog()].push_back(pTpl);
		}
	}
	return true;
}
bool CMainFrame::UpdateComClassMap()
{
	using namespace ld3d;

	m_ComClassMap.clear();


	CoreApiPtr pCore = Project::Instance()->GetCoreApi();
	if(pCore == nullptr)
	{
		return false;
	}
	GameObjectManagerPtr pManager = pCore->GetGameObjectManager();

	for(size_t i = 0; i < pManager->GetPackageCount(); ++i)
	{
		ExtPackage* pPack = pManager->GetPackageByIndex(i);
		for(size_t ii = 0; ii < pPack->GetClassCount(); ++ii)
		{
			ExtPackage::ComponentClass* pClass = pPack->GetClassByIndex(ii);

			if(pClass->m_name == L"PropertyManager")
			{
				continue;
			}
			if(pClass->m_catalog == L"DT")
			{
				continue;
			}
			m_ComClassMap[pClass->m_catalog].push_back(pClass);
		}
	}
	return true;
}
ld3d::ExtPackage::ComponentClass* CMainFrame::FindClassByMenuID(UINT uID)
{
	using namespace ld3d;

	boost::unordered_map<std::wstring, std::vector<ExtPackage::ComponentClass*> >::iterator it = m_ComClassMap.begin();

	int id = ID_COMPONENT_MENU_BASE + 1;
	for(it; it != m_ComClassMap.end(); ++it)
	{
		if(it->second.size() == 0)
		{
			continue;
		}
		for(size_t i = 0; i < it->second.size(); ++i)
		{
			if(id == uID)
			{
				return it->second[i];
			}

			id++;
		}

	}

	return nullptr;
}
void CMainFrame::OnUpdateComponentMenuUI(CCmdUI* pCmdUI)
{
	ld3d::GameObjectPtr pObj = Project::Instance()->GetSelObject();
	pCmdUI->Enable(pObj != ld3d::GameObjectPtr());
}
void CMainFrame::OnUpdateCreateFromTemplateMenuUI(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(true);
}


void CMainFrame::OnRenderingSetting()
{
	// TODO: 在此添加命令处理程序代码

	CRenderingSettingDlg dlg(this);

	if(IDOK != dlg.DoModal())
	{

	}
}


BOOL CMainFrame::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 在此添加专用代码和/或调用基类

	MSG msg;
	msg.hwnd = m_hWnd;
	msg.lParam = lParam;
	msg.wParam = wParam;

	Project::Instance()->HandleMessage(msg);
	
	return CFrameWndEx::OnWndMsg(message, wParam, lParam, pResult);
}


LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CFrameWndEx::WindowProc(message, wParam, lParam);
}


void CMainFrame::OnBuildPreview()
{
	CPreviewWnd wnd(this);

	wnd.DoModal();
}
void CMainFrame::UpdateObjectView(ld3d::GameObjectPtr pRoot)
{
	m_wndObjectView.UpdateObjectView(pRoot);
}
void CMainFrame::UpdatePropGrid(ld3d::GameObjectPtr pObj)
{
	m_wndProperties.UpdateGameObjectProp(pObj);
}
void CMainFrame::OutputInfo(const CString& info)
{
	m_wndOutput.OuputInfo(info);
}
void CMainFrame::outputBuild(const CString& build)
{
	m_wndOutput.OuputInfo(build);
}

void CMainFrame::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnFileSave()
{
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnFileSaveAs()
{
	// TODO: 在此添加命令处理程序代码
}
void CMainFrame::UpdateAssetsView()
{
	m_wndFileView.ScanFolder(Project::Instance()->GetProjectRootPath().wstring().c_str());
}

void CMainFrame::OnFileSaveScene()
{
	using namespace ld3d;
	util_update_obj_property_grid(GameObjectPtr());

	using namespace boost::filesystem;

	path sceneFile = Project::Instance()->GetGameSceneFile();
	if(sceneFile.empty())
	{
		CFileDialog dlg(FALSE, 
				L"scene", 
				NULL, 
				OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
				L"Game Scene Files (*.scene)|*.scene||");

		if(IDOK != dlg.DoModal())
		{
			return;
		}

		sceneFile = dlg.GetPathName().GetString();
	}

	Project::Instance()->SaveScene(sceneFile.wstring().c_str());
	
}


void CMainFrame::OnFileOpenScene()
{
	using namespace ld3d;

	util_update_obj_property_grid(GameObjectPtr());
	util_update_object_view(GameObjectPtr());
	CFileDialog dlg(TRUE, 
				L"scene", 
				NULL, 
				OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
				L"Game Scene Files (*.scene)|*.scene||");

	if(IDOK != dlg.DoModal())
	{
		util_update_object_view(Project::Instance()->Root());
		return;
	}

	ProjectPtr pProject = Project::Instance();

	pProject->CloseScene();
	
	CString file = dlg.GetPathName();

	if(pProject->LoadScene(file) == false)
	{
		MessageBox(L"Fialed to load scene.", L"error", MB_ICONERROR);
		return;
	}

	util_update_object_view(pProject->Root());
}


void CMainFrame::OnFileSaveSceneAs()
{
	using namespace boost::filesystem;

	path sceneFile;

	CFileDialog dlg(FALSE, 
		L"scene", 
		NULL, 
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
		L"Game Scene Files (*.scene)|*.scene||");

	if(IDOK != dlg.DoModal())
	{
		return;
	}

	sceneFile = dlg.GetPathName().GetString();
	
	Project::Instance()->SaveScene(sceneFile.wstring().c_str());
}


void CMainFrame::OnFileNewScene()
{
	using namespace ld3d;
	util_update_obj_property_grid(GameObjectPtr());
	util_update_object_view(GameObjectPtr());

	if(IDYES != MessageBox(L"All unsaved data will be lost, are you sure?", L"error", MB_YESNO))
	{
		util_update_object_view(Project::Instance()->Root());
		return;
	}

	Project::Instance()->CloseScene();
	Project::Instance()->NewScene();

	util_update_object_view(Project::Instance()->Root());
}


void CMainFrame::OnFileNewProject()
{
	using namespace ld3d;
	util_update_obj_property_grid(GameObjectPtr());
	util_update_object_view(GameObjectPtr());

	if(IDYES != MessageBox(L"All unsaved data will be lost, are you sure?", L"error", MB_YESNO))
	{
		util_update_object_view(Project::Instance()->Root());
		return;
	}


	CFileDialog dlg(FALSE, 
				L"gp", 
				NULL, 
				OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
				L"Game Project Files (*.gp)|*.gp||");

	if(IDOK != dlg.DoModal())
	{
		util_update_object_view(Project::Instance()->Root());
		return;
	}

	ProjectPtr pProject = Project::Instance();

	pProject->Close();
	
	CString file = dlg.GetPathName();

	if(pProject->New(file) == false)
	{
		
		MessageBox(L"Fialed to create project, file or directory already exist.", L"error", MB_ICONERROR);
		pProject->Close();
		return;
	}

	util_update_object_view(pProject->Root());
	util_log_info(L"Project created.");

}


void CMainFrame::OnFileOpenProject()
{
	using namespace ld3d;
	util_update_obj_property_grid(GameObjectPtr());
	util_update_object_view(GameObjectPtr());

	CFileDialog dlg(TRUE, 
				L"gp", 
				NULL, 
				OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
				L"Game Project Files (*.gp)|*.gp||");

	if(IDOK != dlg.DoModal())
	{
		return;
	}

	ProjectPtr pProject = Project::Instance();

	pProject->Close();
	
	CString file = dlg.GetPathName();

	if(pProject->Load(file) == false)
	{
		MessageBox(L"Fialed to load project.", L"error", MB_ICONERROR);
		pProject->Close();
		return;
	}

	util_update_object_view(pProject->Root());
	util_log_info(L"Project openned.");
}


void CMainFrame::OnFileSaveProject()
{
	using namespace ld3d;

	util_update_obj_property_grid(GameObjectPtr());

	using namespace boost::filesystem;

	path sceneFile = Project::Instance()->GetGameSceneFile();
	if(sceneFile.empty())
	{
		OnFileSaveScene();
	}

	path projectFile = Project::Instance()->GetProjectFile();
	if(projectFile.empty())
	{
		CFileDialog dlg(FALSE, 
				L"gp", 
				NULL, 
				OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
				L"Game Project Files (*.gp)|*.gp||");

		if(IDOK != dlg.DoModal())
		{
			return;
		}

		projectFile = dlg.GetPathName().GetString();
	}

	if(false == Project::Instance()->Save(projectFile.wstring().c_str()))
	{
		MessageBox(L"Fialed to load project.", L"error", MB_ICONERROR);
		Project::Instance()->Close();
		return;
	}

	util_log_info(L"Project saved.");
}
