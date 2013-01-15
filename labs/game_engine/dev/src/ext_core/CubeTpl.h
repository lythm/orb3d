#pragma once

namespace engine
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