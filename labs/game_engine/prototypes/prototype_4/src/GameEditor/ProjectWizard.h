#pragma once

#include "resource.h"

// CProjectWizard 对话框

class CProjectWizard : public CDialogEx
{
	DECLARE_DYNAMIC(CProjectWizard)

public:
	CProjectWizard(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProjectWizard();

// 对话框数据
	enum { IDD = IDD_PROJECT_NEW_OPEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
};
