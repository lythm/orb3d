#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CProgressDlg 对话框

class CProgressDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProgressDlg)

public:
	CProgressDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProgressDlg();

// 对话框数据
	enum { IDD = IDD_PROGRESS_DLG };

	void					SetPos(int pos);
	void					ProcessMessage();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_progressInfo;
	CProgressCtrl m_progressBar;
	virtual BOOL OnInitDialog();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
