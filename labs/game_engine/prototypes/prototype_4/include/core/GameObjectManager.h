#pragma once


namespace engine
{
	class EXPORT_CLASS GameObjectManager
	{
	public:
		GameObjectManager(void);
		virtual ~GameObjectManager(void);


		typedef boost::function<GameObjectComponentPtr () >			ComponentCreator;

		bool							Initialize();
		void							Release();

		GameObjectPtr					CreateGameObject(const std::wstring& name);
		GameObjectPtr					CreateObjectFromTemplate(const std::string& tpl);
		
		void							RegisterObject();

		void							UpdateObjects();

		GameObjectPtr					GetRoot();
		
		GameObjectComponentPtr			CreateComponent(const std::wstring& name);

		void							RegisterBuildinComponents();
		void							RegisterComponent(const std::wstring& name, const ComponentCreator& creator);
		void							WalkObjectTree();
	private:

		void							ReleaseAllObject();

		void							_tree_walk(GameObject* pObj);

	private:

		GameObjectPtr					m_pRoot;

		boost::unordered_map<std::wstring, ComponentCreator>				m_componentCreator;
		boost::unordered_map<std::string, GameObjectTemplatePtr>			m_templates;
	};
}
