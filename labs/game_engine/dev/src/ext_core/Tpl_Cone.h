#pragma once

namespace ld3d
{
	class Tpl_Cone: public GameObjectTemplate
	{
	public:
		Tpl_Cone(GameObjectManagerPtr pManager, const std::wstring& name);
		virtual ~Tpl_Cone(void);

		GameObjectPtr					CreateGameObject();
		void							Release();
	};


}