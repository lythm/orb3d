#pragma once


namespace engine
{
	class EXPORT_CLASS GameObjectManager
	{
	public:
		GameObjectManager(void);
		virtual ~GameObjectManager(void);


		GameObjectPtr					CreateObject();
		

		void							RegisterObject();

		void							UpdateObjects();

		GameObjectPtr					GetRoot();

	private:
		GameObjectPtr					m_pRoot;
	};


}
