#pragma once



class Project
{
public:
	Project(void);
	virtual ~Project(void);

	bool								New(const _TCHAR* filename);
	bool								Load(const _TCHAR* filename);
	bool								Save(const _TCHAR* filename);
	void								Close();
	
	void								CreateObject_Empty();
	

	engine::GameObjectPtr				CreateObject(const std::wstring& name);
	engine::GameObjectPtr				CreateObjectFromTpl(const std::wstring& name, const std::wstring& tpl);
private:
	
	void								AddDefaultLight();
private:
	CString								m_filePath;

	PathManagerPtr						m_pPathManager;

	int									m_objNo;
};

