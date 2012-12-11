#pragma once



class Project
{
public:
	Project(void);
	virtual ~Project(void);

	bool								New();
	bool								Load(const _TCHAR* filename);
	bool								Save(const _TCHAR* filename);
	void								Close();
	
	static ProjectPtr					Instance();
private:

	void								AddDefaultLight();
private:

	CString								m_filePath;
	static ProjectPtr					m_pProject;
};

