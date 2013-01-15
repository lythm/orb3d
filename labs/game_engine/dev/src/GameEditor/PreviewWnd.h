#pragma once


// CPreviewWnd 对话框

class CPreviewWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CPreviewWnd)

public:
	CPreviewWnd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPreviewWnd();

// 对话框数据
	enum { IDD = IDD_PREVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();


private:
	ld3d::RenderTargetPtr				m_pRenderTarget;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
