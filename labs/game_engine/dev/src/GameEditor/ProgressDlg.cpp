// ProgressDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GameEditor.h"
#include "ProgressDlg.h"
#include "afxdialogex.h"


// CProgressDlg 对话框

IMPLEMENT_DYNAMIC(CProgressDlg, CDialogEx)

	CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProgressDlg::IDD, pParent)
{

}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_INFO, m_progressInfo);
	DDX_Control(pDX, IDC_PROGRESS, m_progressBar);
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialogEx)
	ON_WM_ACTIVATE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CProgressDlg 消息处理程序


BOOL CProgressDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_progressBar.SetRange(0, 100);
	m_progressBar.SetPos(0);

	
	return TRUE;
	// 异常: OCX 属性页应返回 FALSE
}
void CProgressDlg::ProcessMessage()
{
	MSG msg = {0};
	if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
}

void CProgressDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 在此处添加消息处理程序代码
}


void CProgressDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
}
void CProgressDlg::SetPos(int pos)
{
	m_progressBar.SetPos(pos);
}