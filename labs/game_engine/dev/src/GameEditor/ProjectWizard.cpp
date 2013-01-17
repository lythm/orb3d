// ProjectWizard.cpp : 实现文件
//

#include "stdafx.h"
#include "GameEditor.h"
#include "ProjectWizard.h"
#include "afxdialogex.h"
#include "resource.h"
#include "Project.h"
#include "editor_utils.h"


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
	ON_BN_CLICKED(IDC_PW_BUTTON_NEW, &CProjectWizard::OnBnClickedPwButtonNew)
	ON_BN_CLICKED(IDC_PW_BUTTON_OPEN, &CProjectWizard::OnBnClickedPwButtonOpen)
END_MESSAGE_MAP()


// CProjectWizard 消息处理程序


void CProjectWizard::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}


BOOL CProjectWizard::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;
}



void CProjectWizard::OnBnClickedPwButtonNew()
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

	ProjectPtr pProject = Project::Instance();

	pProject->Close();
	
	CString file = dlg.GetPathName();

	if(pProject->New(file) == false)
	{
		
		MessageBox(L"Fialed to create project, file or directory already exist.", L"error", MB_ICONERROR);
		util_log_info(L"Fialed to create project, file or directory already exist.");

		pProject->Close();
		CDialogEx::OnCancel();
		return;
	}

	util_log_info(L"Project created.");

	CDialogEx::OnOK();
}


void CProjectWizard::OnBnClickedPwButtonOpen()
{
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
		util_log_info(L"Fialed to load project.");

		pProject->Close();
		CDialogEx::OnCancel();
		return;
	}

	util_log_info(L"Project openned.");

	CDialogEx::OnOK();
}
