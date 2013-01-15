#pragma once

namespace ld3d
{
	class CubeTpl : public GameObjectTemplate
	{
	public:
		CubeTpl(GameObjectManagerPtr pManager, const std::wstring& name);
		virtual ~CubeTpl(void);

		GameObjectPtr					CreateGameObject();
		void							Release();
	};


}