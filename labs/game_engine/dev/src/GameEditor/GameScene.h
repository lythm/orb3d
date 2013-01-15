#pragma once


class GameScene
{
public:
	GameScene(ld3d::CoreApiPtr pCore);
	virtual ~GameScene(void);

	bool										Load(boost::filesystem::path file);
	bool										Save(boost::filesystem::path file);
	void										Close();
	bool										New();

	const boost::filesystem::path&				GetFileName();


	void										CreateObject_Empty();
	ld3d::GameObjectPtr						CreateObject(const std::wstring& name);
	ld3d::GameObjectPtr						CreateObjectFromTpl(const std::wstring& name, const std::wstring& tpl);
	ld3d::GameObjectComponentPtr				CreateGameObjectComponent(const std::wstring& name);

	ld3d::GameObjectPtr						Root();
private:
	void										AddDefaultLight();
private:
	boost::filesystem::path						m_filepath;
	ld3d::CoreApiPtr							m_pCore;

	int											m_objNo;
};

