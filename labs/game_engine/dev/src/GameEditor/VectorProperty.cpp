#include "StdAfx.h"
#include "VectorProperty.h"

#define AFX_PROP_HAS_BUTTON 0x0002
namespace custom_property
{
	VectorProperty::VectorProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr, DWORD_PTR dwData) : CMFCPropertyGridProperty(strName, varValue, lpszDescr, dwData)
	{
		m_dwFlags = AFX_PROP_HAS_BUTTON;
	}


	VectorProperty::~VectorProperty(void)
	{
	}
	void VectorProperty::OnClickButton(CPoint point)
	{
	}

}
