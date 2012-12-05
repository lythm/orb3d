#pragma once

namespace custom_property
{
	class VectorProperty : public CMFCPropertyGridProperty
	{
	public:

		VectorProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0);
		virtual ~VectorProperty(void);

		void OnClickButton(CPoint point);
	};


}
