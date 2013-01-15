// RenderingSettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GameEditor.h"
#include "RenderingSettingDlg.h"
#include "afxdialogex.h"


// CRenderingSettingDlg 对话框

IMPLEMENT_DYNAMIC(CRenderingSettingDlg, CDialogEx)

CRenderingSettingDlg::CRenderingSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRenderingSettingDlg::IDD, pParent)
{

}

CRenderingSettingDlg::~CRenderingSettingDlg()
{
}

void CRenderingSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRenderingSettingDlg, CDialogEx)
END_MESSAGE_MAP()


// CRenderingSettingDlg 消息处理程序
