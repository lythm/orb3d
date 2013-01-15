#include "stdafx.h"
#include "InspectorCtrl.h"

#include "resource.h"

CInspectorCtrl::CInspectorCtrl(void)
{
}


CInspectorCtrl::~CInspectorCtrl(void)
{
}
BEGIN_MESSAGE_MAP(CInspectorCtrl, CWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


int CInspectorCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
bool CInspectorCtrl::Create(const TCHAR* szName, const CRect& rc, CWnd* pParent)
{
	return CWnd::Create(L"AfxWnd", szName, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rc, pParent, IDD_INSPECTOR_VIEW) == TRUE;
}
