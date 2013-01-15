#pragma once

namespace ld3d
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