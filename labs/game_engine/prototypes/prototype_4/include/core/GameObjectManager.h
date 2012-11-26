#pragma once


namespace engine
{
	class EXPORT_CLASS GameObjectManager
	{
	public:
		GameObjectManager(void);
		virtual ~GameObjectManager(void);


//		typedef boost::function<GameObjectComponentPtr () >			GameObjectComponentCreator;


		GameObjectPtr					CreateGameObject(const std::wstring& name);
		GameObjectPtr					CreateObjectFromTemplate(const std::string& tpl);
		
		void							RegisterObject();

		void							UpdateObjects();

		GameObjectPtr					GetRoot();
		
		void							ReleaseAllObject();

		GameObjectComponentPtr			CreateObjectComponent(const std::string& name);

		void							RegisterObjectComponent();

		void							WalkObjectTree();
	private:

		void							_tree_walk(GameObject* pObj);

	private:

		GameObjectPtr					m_pRoot;

		//boost::unordered_map<std::string, 
	};


}
