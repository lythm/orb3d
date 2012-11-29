#pragma once



class Project
{
public:
	Project(void);
	virtual ~Project(void);

	bool								New(const _TCHAR* name);
	void								Load();
	bool								Save();
	void								Release();

	static ProjectPtr					Instance();
private:
	std::wstring						m_name;

	static ProjectPtr					m_pProject;
};

