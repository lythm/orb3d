#pragma once

#include "TemplateViewTree.h"

class CTemplateViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

// CTemplateView

class CTemplateView : public CDockablePane
{
	DECLARE_DYNAMIC(CTemplateView)

public:
	CTemplateView();
	virtual ~CTemplateView();
	void AdjustLayout();
	void OnChangeVisualStyle();

protected:
	CTemplateViewToolBar m_wndToolBar;
	CTemplateViewTree m_wndTemplateView;
	CImageList m_ObjectViewImages;
	UINT m_nCurrSort;
// ÖØÐ´
public:

	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnNewFolder();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnChangeActiveTab(WPARAM, LPARAM);
	afx_msg void OnSort(UINT id);
	afx_msg void OnUpdateSort(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOvRename();
};


