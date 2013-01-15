#pragma once


class GameScene
{
public:
	GameScene(engine::CoreApiPtr pCore);
	virtual ~GameScene(void);

	bool										Load(boost::filesystem::path file);
	bool										Save(boost::filesystem::path file);
	void										Close();
	bool										New();

	const boost::filesystem::path&				GetFileName();


	void										CreateObject_Empty();
	engine::GameObjectPtr						CreateObject(const std::wstring& name);
	engine::GameObjectPtr						CreateObjectFromTpl(const std::wstring& name, const std::wstring& tpl);
	engine::GameObjectComponentPtr				CreateGameObjectComponent(const std::wstring& name);
private:
	void										AddDefaultLight();
private:
	boost::filesystem::path						m_filepath;
	engine::CoreApiPtr							m_pCore;

	int											m_objNo;
};

