#pragma once

#include "resource.h"
// CAppSettingsDlg 对话框

class CAppSettingsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAppSettingsDlg)

public:
	CAppSettingsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAppSettingsDlg();

// 对话框数据
	enum { IDD = IDD_APPSETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
