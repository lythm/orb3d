#pragma once


// CObjectPropertyGrid

class CObjectPropertyGrid : public CMFCPropertyGridCtrl
{
	DECLARE_DYNAMIC(CObjectPropertyGrid)

public:
	CObjectPropertyGrid();
	virtual ~CObjectPropertyGrid();


	void										UpdateGameObjectProp(engine::GameObjectPtr pObj);
private:
	CMFCPropertyGridProperty*					CreateProperty(engine::Property* p);
	
private:
	engine::GameObjectPtr						m_pObj;

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnPropertyChanged(CMFCPropertyGridProperty* pProp) const;
};


