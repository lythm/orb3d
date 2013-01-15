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

	void								CloseScene();
	bool								SaveScene(const _TCHAR* filename);
	bool								LoadScene(const _TCHAR* filename);
	
	void								CreateObject_Empty();
	engine::GameObjectPtr				CreateObject(const std::wstring& name);
	engine::GameObjectPtr				CreateObjectFromTpl(const std::wstring& name, const std::wstring& tpl);
	engine::GameObjectComponentPtr		CreateGameObjectComponent(const std::wstring& name);
	engine::CoreApiPtr					GetCoreApi();
	RendererPtr							GetRenderer();

	void								ResizeRenderer(int cx, int cy);

	void								SelectObject(engine::GameObjectPtr pObj);
	engine::GameObjectPtr				GetSelObject();

	engine::GameObjectPtr				Root();

	void								HandleMessage(MSG& msg);

	void								Render();

	bool								ShowingGrid();
	void								ShowGrid(bool bShow);

	static ProjectPtr					Instance();

	void								SetClearColor(const math::Color4& clr);
	const math::Color4					GetClearColor();

	boost::filesystem::path				GetProjectPath();

	boost::filesystem::path				GetGameSceneFile();
private:

	bool								CreateNewProject(const CString& dir);
	void								Reset();

	bool								InitRenderer();
	void								ReleaseRenderer();

	bool								InitEngine();
	void								ReleaseEngine();

private:
	
	bool								CopyDirectory(boost::filesystem::path src, boost::filesystem::path dst);
private:
	boost::filesystem::path				m_filePath;

	PathManagerPtr						m_pPathManager;
	
	RendererPtr							m_pRenderer;

	engine::CoreApiPtr					m_pCore;

	engine::GameObjectPtr				m_pSelObject;

	math::Color4						m_clearClr;
	GameScenePtr						m_pScene;
	
	static engine::PoolAllocator		s_Allocator;
	static ProjectPtr					s_pInstance;
};


