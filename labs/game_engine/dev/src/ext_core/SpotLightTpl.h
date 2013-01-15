#pragma once

namespace ld3d
{
	class SpotLightTpl : public GameObjectTemplate
	{
	public:
		SpotLightTpl(GameObjectManagerPtr pManager, const std::wstring& name);
		virtual ~SpotLightTpl(void);

		GameObjectPtr					CreateGameObject();
		void							Release();
	};


}