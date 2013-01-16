#pragma once


namespace ld3d
{
	class Tpl_Sphere : public GameObjectTemplate
	{
	public:
		Tpl_Sphere(GameObjectManagerPtr pManager, const std::wstring& name);
		virtual ~Tpl_Sphere(void);

		void											Release();
		GameObjectPtr									CreateGameObject();
	};


}