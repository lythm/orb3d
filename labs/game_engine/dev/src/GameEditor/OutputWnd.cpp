
#include "stdafx.h"

#include "OutputWnd.h"
#include "Resource.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputWnd::COutputWnd()
{
}

COutputWnd::~COutputWnd()
{
}

BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建选项卡窗口:
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("未能创建输出选项卡窗口\n");
		return -1;      // 未能创建
	}

	// 创建输出窗格:
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
	
	if(!m_wndOutputMessage.Create(rectDummy, &m_wndTabs) ||
		!m_wndOutputBuild.Create(rectDummy, &m_wndTabs))
	{
		TRACE0("未能创建输出窗口\n");
		return -1;      // 未能创建
	}

	UpdateFonts();

	m_wndTabs.AddTab(&m_wndOutputMessage, L"General", (UINT)2);
	m_wndTabs.AddTab(&m_wndOutputBuild, L"Build", (UINT)3);

	return 0;
}

void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// 选项卡控件应覆盖整个工作区:
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void COutputWnd::OuputInfo(const CString& string)
{
	m_wndOutputMessage.AddLine(string);
}
void COutputWnd::OuputBuild(const CString& string)
{
	m_wndOutputBuild.AddLine(string);
}

void COutputWnd::UpdateFonts()
{
	m_wndOutputMessage.SetFont(&afxGlobalData.fontRegular);
	m_wndOutputBuild.SetFont(&afxGlobalData.fontRegular);
}


HBRUSH COutputWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CEdit::OnCtlColor(pDC, pWnd, nCtlColor);

	return (HBRUSH)GetStockObject(WHITE_BRUSH);
}


COutputEdit::COutputEdit()
{
	
}
COutputEdit::~COutputEdit()
{
}
BEGIN_MESSAGE_MAP(COutputEdit, CEdit)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_VIEW_OUTPUTWND, OnViewOutput)
	ON_WM_WINDOWPOSCHANGING()

	ON_COMMAND(ID_OUTPUT_EDIT_SELECT_ALL, &COutputEdit::OnOutputEditSelectAll)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL COutputEdit::Create(const RECT& rect, CWnd* pParentWnd)
{
	const DWORD dwEditStyle = WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_READONLY ;

	return CEdit::Create(dwEditStyle, rect, pParentWnd, 0);
}


void COutputEdit::AddLine(const CString& l)
{
	m_buffer += l;
	m_buffer += "\r\n";

	SetWindowText(m_buffer);

	ScrollToEnd();
}
void COutputEdit::ScrollToEnd()
{
	int lines = GetLineCount();
	LineScroll(lines);
}
void COutputEdit::OnViewOutput()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();

	}
}

void COutputEdit::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_OUTPUT_POPUP);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
	else
	{
		pSumMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	}

	SetFocus();
}

void COutputEdit::OnEditCopy()
{
	Copy();
}

void COutputEdit::OnEditClear()
{
	m_buffer = L"";
	SetWindowText(m_buffer);
}

void COutputEdit::OnOutputEditSelectAll()
{
	this->SetSel(0, -1);
}



HBRUSH COutputEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CEdit::OnCtlColor(pDC, pWnd, nCtlColor);

	return (HBRUSH)GetStockObject(WHITE_BRUSH);
}

