// StartDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "StartDialog.h"
#include "afxdialogex.h"


// CStartDialog 对话框

IMPLEMENT_DYNAMIC(CStartDialog, CDialogEx)

CStartDialog::CStartDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStartDialog::IDD, pParent)
{

}

CStartDialog::~CStartDialog()
{
}

void CStartDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStartDialog, CDialogEx)
END_MESSAGE_MAP()


// CStartDialog 消息处理程序
