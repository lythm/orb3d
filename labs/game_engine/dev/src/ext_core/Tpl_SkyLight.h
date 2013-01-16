#pragma once
namespace ld3d
{
	class Tpl_SkyLight : public GameObjectTemplate
	{
	public:
		Tpl_SkyLight(GameObjectManagerPtr pManager, const std::wstring& name);
		virtual ~Tpl_SkyLight(void);

		GameObjectPtr					CreateGameObject();
		void							Release();
	};


}