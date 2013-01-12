// PreviewWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "GameEditor.h"
#include "PreviewWnd.h"
#include "afxdialogex.h"
#include "AppContext.h"

#include "Renderer.h"

// CPreviewWnd 对话框

IMPLEMENT_DYNAMIC(CPreviewWnd, CDialogEx)

CPreviewWnd::CPreviewWnd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPreviewWnd::IDD, pParent)
{

}

CPreviewWnd::~CPreviewWnd()
{
}

void CPreviewWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPreviewWnd, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPreviewWnd 消息处理程序


BOOL CPreviewWnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	using namespace engine;

	CRect rc;

	GetClientRect(rc);


	m_pRenderTarget = AppContext::GetCoreApi()->GetSysGraphics()->CreateRenderWindow(m_hWnd, rc.Width(), rc.Height(), G_FORMAT_R8G8B8A8_UNORM, G_FORMAT_D24_UNORM_S8_UINT, 2, 1, 0, true);
	
	AppContext::GetCoreApi()->GetSysGraphics()->SetRenderWindow(m_pRenderTarget);
	AppContext::ResizeRenderer(rc.Width(), rc.Height());
	
	SetTimer(99, 10, nullptr);


	AppContext::GetCoreApi()->CreatGameObjectFromTemplate(L"VoxelWorld", L"");

	return TRUE;
}


void CPreviewWnd::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	KillTimer(99);
	AppContext::GetCoreApi()->GetSysGraphics()->SetRenderWindow(engine::RenderTargetPtr());

	int w = AppContext::GetCoreApi()->GetSysGraphics()->GetFrameBufferWidth();
	int h = AppContext::GetCoreApi()->GetSysGraphics()->GetFrameBufferHeight();

	AppContext::ResizeRenderer(w, h);

	m_pRenderTarget->Release();
	m_pRenderTarget.reset();


	CDialogEx::OnClose();
}



void CPreviewWnd::OnTimer(UINT_PTR nIDEvent)
{
	AppContext::GetRenderer()->Render();
	
	CDialogEx::OnTimer(nIDEvent);
}


void CPreviewWnd::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if(m_pRenderTarget != engine::RenderTargetPtr())
	{
		AppContext::ResizeRenderer(cx, cy);
	}
	// TODO: 在此处添加消息处理程序代码
}
