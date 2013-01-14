// ProjectWizard.cpp : 实现文件
//

#include "stdafx.h"
#include "GameEditor.h"
#include "ProjectWizard.h"
#include "afxdialogex.h"


// CProjectWizard 对话框

IMPLEMENT_DYNAMIC(CProjectWizard, CDialogEx)

CProjectWizard::CProjectWizard(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProjectWizard::IDD, pParent)
{

}

CProjectWizard::~CProjectWizard()
{
}

void CProjectWizard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProjectWizard, CDialogEx)
END_MESSAGE_MAP()


// CProjectWizard 消息处理程序


void CProjectWizard::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}
