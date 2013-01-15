#pragma once


namespace ld3d
{
	class SphereTpl : public GameObjectTemplate
	{
	public:
		SphereTpl(GameObjectManagerPtr pManager, const std::wstring& name);
		virtual ~SphereTpl(void);

		void											Release();
		GameObjectPtr									CreateGameObject();
	};


}