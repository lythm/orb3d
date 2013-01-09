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
	void								CreateObject_FromTemplate_Cube();
	void								CreateObject_FromTemplate_Cone();
	void								CreateObject_FromTemplate_Sphere();
	void								CreateObject_FromTemplate_Plane();

	void								CreateObject_FromTemplate_DirLight();
	void								CreateObject_FromTemplate_PointLight();
	void								CreateObject_FromTemplate_SpotLight();
	void								CreateObject_FromTemplate_SkyLight();

	engine::GameObjectPtr				CreateObject(const std::wstring& name);

private:
	
	void								AddDefaultLight();
private:
	CString								m_filePath;

	PathManagerPtr						m_pPathManager;

	int									m_objNo;
};

