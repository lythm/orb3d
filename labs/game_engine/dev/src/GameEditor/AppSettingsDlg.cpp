// AppSettingsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AppSettingsDlg.h"
#include "afxdialogex.h"


// CAppSettingsDlg 对话框

IMPLEMENT_DYNAMIC(CAppSettingsDlg, CDialogEx)

CAppSettingsDlg::CAppSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAppSettingsDlg::IDD, pParent)
{

}

CAppSettingsDlg::~CAppSettingsDlg()
{
}

void CAppSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAppSettingsDlg, CDialogEx)
END_MESSAGE_MAP()


// CAppSettingsDlg 消息处理程序
