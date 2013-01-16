#pragma once
namespace ld3d
{
	class Tpl_DirLight : public GameObjectTemplate
	{
	public:
		Tpl_DirLight(GameObjectManagerPtr pManager, const std::wstring& name);
		virtual ~Tpl_DirLight(void);

		GameObjectPtr					CreateGameObject();
		void							Release();
	};


}