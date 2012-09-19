#pragma once


namespace engine
{
	class Scene
	{
	public:
		Scene(void);
		virtual ~Scene(void);


	private:

		GameObjectManagerPtr			m_pObjectManager;

	};


}