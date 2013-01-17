
// GameEditorView.cpp : CGameEditorView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GameEditor.h"
#endif

#include "GameEditorDoc.h"
#include "GameEditorView.h"


#include "MainFrm.h"
#include "ObjectView.h"

#include "GridMesh.h"
#include "Renderer.h"


#include "editor_utils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameEditorView

IMPLEMENT_DYNCREATE(CGameEditorView, CView)

BEGIN_MESSAGE_MAP(CGameEditorView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CGameEditorView 构造/析构

CGameEditorView::CGameEditorView()
{
	// TODO: 在此处添加构造代码

//	m_pGrid = NULL;

}

CGameEditorView::~CGameEditorView()
{
	
}

BOOL CGameEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGameEditorView 绘制

void CGameEditorView::OnDraw(CDC* pDC)
{
	CGameEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
}

void CGameEditorView::OnRButtonUp(UINT nFlags , CPoint point)
{

	RendererPtr pRenderer = Project::Instance()->GetRenderer();

	if(pRenderer)
	{
		pRenderer->OnMouseRButtonUp(nFlags, point);
	}

	
	ClientToScreen(&point);
	OnContextMenu(this, point);
	
}

void CGameEditorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGameEditorView 诊断

#ifdef _DEBUG
void CGameEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CGameEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGameEditorDoc* CGameEditorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameEditorDoc)));
	return (CGameEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CGameEditorView 消息处理程序


void CGameEditorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
}



void CGameEditorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnTimer(nIDEvent);
}


void CGameEditorView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if(cx != 0 && cy != 0)
	{
		Project::Instance()->ResizeRenderer(cx, cy);
		
	}
}

void CGameEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	RendererPtr pRenderer = Project::Instance()->GetRenderer();
	
	if(pRenderer)
	{
		pRenderer->OnMouseMove(nFlags, point);
	}

	CView::OnMouseMove(nFlags, point);
}


void CGameEditorView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类


}


void CGameEditorView::OnDestroy()
{
	//AppContext::ReleaseContext();
	util_set_rendering_wnd(nullptr);
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}


void CGameEditorView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	// TODO: 在此添加消息处理程序代码和/或调用默认值



	CView::OnMouseHWheel(nFlags, zDelta, pt);
}


BOOL CGameEditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	RendererPtr pRenderer = Project::Instance()->GetRenderer();

	if(pRenderer)
	{
		pRenderer->OnMouseWheel(nFlags, zDelta, pt);
	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CGameEditorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	RendererPtr pRenderer = Project::Instance()->GetRenderer();

	if(pRenderer)
	{
		pRenderer->OnMouseRButtonDown(nFlags, point);
	}

	CView::OnRButtonDown(nFlags, point);
}


BOOL CGameEditorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rc;
	GetClientRect(rc);
	CBrush br(RGB(0, 0,0));
	pDC->FillRect(rc, &br);

	return TRUE;
}


int CGameEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	util_set_rendering_wnd(this);
		
	return 0;
}


void CGameEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CView::OnLButtonDblClk(nFlags, point);
}


void CGameEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(Project::Instance()->GetRenderer())
	{
		Project::Instance()->GetRenderer()->OnMouseLButtonClick(nFlags, point);
	}
	CView::OnLButtonUp(nFlags, point);
}

