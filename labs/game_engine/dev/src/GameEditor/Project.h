#pragma once



class Project
{
public:
	Project(void);
	virtual ~Project(void);

	bool								New(const _TCHAR* filename);
	bool								Load(const _TCHAR* filename);
	bool								Save(const _TCHAR* filename);
	bool								Save();
	void								Close();

	bool								NewScene();
	void								CloseScene();
	bool								SaveScene(const _TCHAR* filename);
	bool								LoadScene(const _TCHAR* filename);
	
	void								CreateObject_Empty();
	ld3d::GameObjectPtr					CreateObject(const std::wstring& name);
	ld3d::GameObjectPtr					CreateObjectFromTpl(const std::wstring& name, const std::wstring& tpl);
	ld3d::GameObjectComponentPtr		CreateGameObjectComponent(const std::wstring& name);
	ld3d::CoreApiPtr					GetCoreApi();
	RendererPtr							GetRenderer();

	void								ResizeRenderer(int cx, int cy);

	void								SelectObject(ld3d::GameObjectPtr pObj);
	ld3d::GameObjectPtr					GetSelObject();

	ld3d::GameObjectPtr					Root();

	void								HandleMessage(MSG& msg);

	void								Render();
	void								RenderPreview();

	bool								ShowingGrid();
	void								ShowGrid(bool bShow);

	static ProjectPtr					Instance();

	void								SetClearColor(const math::Color4& clr);
	const math::Color4					GetClearColor();

	boost::filesystem::path				GetProjectRootPath();

	boost::filesystem::path				GetGameSceneFile();
	boost::filesystem::path				GetProjectFile();

	boost::filesystem::path				GetRelativePath(boost::filesystem::path p);

	void								RestoreCurrentDirectory();
private:

	bool								CreateNewProject(const CString& dir);
	void								Reset();

	bool								InitRenderer();
	void								ReleaseRenderer();

	bool								InitEngine();
	void								ReleaseEngine();

private:
	
	
private:
	boost::filesystem::path				m_filePath;

	PathManagerPtr						m_pPathManager;
	
	RendererPtr							m_pRenderer;

	ld3d::CoreApiPtr					m_pCore;

	ld3d::GameObjectPtr					m_pSelObject;

	math::Color4						m_clearClr;
	GameScenePtr						m_pScene;
	
	static ProjectPtr					s_pInstance;
};


