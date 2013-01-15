#pragma once


class CInspectorCtrl : public CWnd
{
public:
	CInspectorCtrl(void);
	virtual ~CInspectorCtrl(void);


	bool										Create(const TCHAR* szName, const CRect& rc, CWnd* pParent);

private:

public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

