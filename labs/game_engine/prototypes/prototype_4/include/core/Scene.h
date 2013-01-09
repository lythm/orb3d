#pragma once


namespace engine
{
	class Scene
	{
	public:
		Scene(void);
		virtual ~Scene(void);

		GameObjectPtr					Root();
		void							Reset();
		void							Release();
		void							Update();

		bool							Load(DataStreamPtr pStream);

	private:

		GameObjectManagerPtr			m_pObjectManager;
		GameObjectPtr					m_pRoot;


	};


}
