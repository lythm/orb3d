#pragma once


// CRenderingSettingDlg 对话框

class CRenderingSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRenderingSettingDlg)

public:
	CRenderingSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRenderingSettingDlg();

// 对话框数据
	enum { IDD = IDD_RENDERING_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
