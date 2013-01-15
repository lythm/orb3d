#pragma once



// CObjectPropertyGrid

class CObjectPropertyGrid : public CMFCPropertyGridCtrl
{
	DECLARE_DYNAMIC(CObjectPropertyGrid)

public:
	CObjectPropertyGrid();
	virtual ~CObjectPropertyGrid();


	void										UpdateGameObjectProp(ld3d::GameObjectPtr pObj);
	void										AddPropertySet(ld3d::PropertySetPtr pPropSet);

private:
	CMFCPropertyGridProperty*					CreateProperty(ld3d::Property* p);
	
private:
	ld3d::GameObjectPtr						m_pObj;
	
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnPropertyChanged(CMFCPropertyGridProperty* pProp) const;
	afx_msg void OnDestroy();
	afx_msg void OnNcDestroy();
};


