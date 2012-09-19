#pragma once


namespace engine
{
	class Scene
	{
	public:
		Scene(void);
		virtual ~Scene(void);

		bool							Load();


	private:

		GameObjectManagerPtr			m_pObjectManager;

	};


}