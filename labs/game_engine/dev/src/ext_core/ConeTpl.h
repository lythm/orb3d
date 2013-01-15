#pragma once

namespace engine
{
	class ConeTpl: public GameObjectTemplate
	{
	public:
		ConeTpl(GameObjectManagerPtr pManager, const std::wstring& name);
		virtual ~ConeTpl(void);

		GameObjectPtr					CreateGameObject();
		void							Release();
	};


}