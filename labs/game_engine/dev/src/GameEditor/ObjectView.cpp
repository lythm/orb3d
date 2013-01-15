
#include "stdafx.h"
#include "MainFrm.h"
#include "ObjectView.h"
#include "Resource.h"
#include "GameEditor.h"
#include "Renderer.h"
#include "Project.h"
#include "editor_utils.h"

class CObjectViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CObjectView;

	DECLARE_SERIAL(CObjectViewMenuButton)

public:
	CObjectViewMenuButton(HMENU hMenu = NULL) : CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz = TRUE,
		BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CMFCToolBar::GetImages();

		CAfxDrawState ds;
		pImages->PrepareDrawImage(ds);

		CMFCToolBarMenuButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage(ds);
	}
};

IMPLEMENT_SERIAL(CObjectViewMenuButton, CMFCToolBarMenuButton, 1)

//////////////////////////////////////////////////////////////////////
// 构造/析构
//////////////////////////////////////////////////////////////////////

CObjectView::CObjectView()
{
	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
}

CObjectView::~CObjectView()
{
}

BEGIN_MESSAGE_MAP(CObjectView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_NEW_FOLDER, OnNewFolder)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)
	ON_COMMAND(ID_OV_DELOBJ, &CObjectView::OnOvDelobj)
	ON_COMMAND(ID_OV_RENAME, &CObjectView::OnOvRename)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectView 消息处理程序

int CObjectView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_EX_DOUBLEBUFFER | TVS_TRACKSELECT | TVS_SHOWSELALWAYS| TVS_EDITLABELS | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectView.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("未能创建对象视图\n");
		return -1;      // 未能创建
	}

	
	// 加载图像:
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SORT);
	m_wndToolBar.LoadToolBar(IDR_SORT, 0, 0, TRUE /* 已锁定*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	CMenu menuSort;
	menuSort.LoadMenu(IDR_POPUP_SORT);

	m_wndToolBar.ReplaceButton(ID_SORT_MENU, CObjectViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));

	CObjectViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CObjectViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->m_bText = FALSE;
		pButton->m_bImage = TRUE;
		pButton->SetImage(GetCmdMgr()->GetCmdImage(m_nCurrSort));
		pButton->SetMessageWnd(this);
	}

	UpdateObjectView(Project::Instance()->Root());

	return 0;
}

void CObjectView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}
void CObjectView::UpdateObjectView(ld3d::GameObjectPtr pRoot)
{
	using namespace ld3d;

	m_wndObjectView.UpdateGameObjectTree(pRoot);
	m_wndObjectView.Expand(m_wndObjectView.GetRootItem(), TVE_EXPAND);
}

void CObjectView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndObjectView;
	ASSERT_VALID(pWndTree);


	bool bShow = false;

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	CMenu menu;
	menu.LoadMenu(IDR_OV_CONTEXT);
	CMenu* pSumMenu = menu.GetSubMenu(0);
	
	pSumMenu->EnableMenuItem(ID_OV_DELOBJ, MF_ENABLED);
	pSumMenu->EnableMenuItem(ID_OV_RENAME, MF_ENABLED);
	if (point != CPoint(-1, -1))
	{
		// 选择已单击的项:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL && (TVHT_ONITEMLABEL & flags))
		{
			bShow = true;
			pWndTree->SelectItem(hTreeItem);
		}
		
		if(hTreeItem == pWndTree->GetRootItem())
		{
			bShow = true;
			pSumMenu->EnableMenuItem(ID_OV_DELOBJ, MF_GRAYED);
			pSumMenu->EnableMenuItem(ID_OV_RENAME, MF_GRAYED);
		}
	}
	
	pWndTree->SetFocus();
	
	if(bShow)
	{
		pSumMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	}
}

void CObjectView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndObjectView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

BOOL CObjectView::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

void CObjectView::OnSort(UINT id)
{
	if (m_nCurrSort == id)
	{
		return;
	}

	m_nCurrSort = id;

	CObjectViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CObjectViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->SetImage(GetCmdMgr()->GetCmdImage(id));
		m_wndToolBar.Invalidate();
		m_wndToolBar.UpdateWindow();
	}
}

void CObjectView::OnUpdateSort(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrSort);
}

void CObjectView::OnNewFolder()
{
	AfxMessageBox(_T("新建文件夹..."));
}

void CObjectView::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_wndObjectView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CObjectView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndObjectView.SetFocus();
}

void CObjectView::OnChangeVisualStyle()
{
	m_ObjectViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("无法加载位图: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_ObjectViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_ObjectViewImages.Add(&bmp, RGB(255, 0, 0));

	m_wndObjectView.SetImageList(&m_ObjectViewImages, TVSIL_NORMAL);

	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* 锁定*/);
}


//void CObjectView::OnIdrOvContext()
//{
//	// TODO: 在此添加命令处理程序代码
//}


void CObjectView::OnOvDelobj()
{
	// TODO: 在此添加命令处理程序代码
	using namespace ld3d;

	util_update_obj_property_grid(GameObjectPtr());

	HTREEITEM hItem = m_wndObjectView.GetSelectedItem();
	
	GameObjectPtr pObj = m_wndObjectView.GetGameObject(hItem);

	pObj->Clear();
	
	m_wndObjectView.EraseItem(hItem);

}


void CObjectView::OnOvRename()
{
	HTREEITEM hItem = m_wndObjectView.GetSelectedItem();
	if(hItem == NULL)
	{
		return;
	}
	m_wndObjectView.EditLabel(hItem);
}
void CObjectView::ClearSelection()
{
	Project::Instance()->SelectObject(ld3d::GameObjectPtr());
	m_wndObjectView.SelectItem(nullptr);
}