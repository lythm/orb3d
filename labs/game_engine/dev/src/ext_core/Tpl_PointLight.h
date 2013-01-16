#pragma once


namespace ld3d
{
	class Tpl_PointLight : public GameObjectTemplate
	{
	public:
		Tpl_PointLight(GameObjectManagerPtr pManager, const std::wstring& name);
		virtual ~Tpl_PointLight(void);

		GameObjectPtr					CreateGameObject();
		void							Release();
	};


}