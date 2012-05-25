#pragma once


namespace engine
{
	class GameObjectManager
	{
	public:
		GameObjectManager(void);
		virtual ~GameObjectManager(void);

		bool										RegisterComponents();

		bool										LoadExtension(const char* szFile);

		void										Release();

		GameObjectPtr								CreateGameObject();

		GameObjectComponentPtr						CreateComponent();

	private:

	};


}