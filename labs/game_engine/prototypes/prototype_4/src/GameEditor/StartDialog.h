#pragma once

#include "resource.h"

// CStartDialog 对话框

class CStartDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CStartDialog)

public:
	CStartDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStartDialog();

// 对话框数据
	enum { IDD = IDD_STARTUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
