#pragma once


namespace engine
{
	class EXPORT_CLASS GameObjectManager
	{
	public:
		GameObjectManager(void);
		virtual ~GameObjectManager(void);


//		typedef boost::function<GameObjectComponentPtr () >			GameObjectComponentCreator;



		GameObjectPtr					CreateObjectFromTemplate(const std::string& tpl);
		
		void							RegisterObject();

		void							UpdateObjects();

		GameObjectPtr					GetRoot();
		
		void							ReleaseAllObject();

		GameObjectComponentPtr			CreateObjectComponent(const std::string& name);
	private:
		GameObjectPtr					m_pRoot;

		//boost::unordered_map<std::string, 
	};


}
