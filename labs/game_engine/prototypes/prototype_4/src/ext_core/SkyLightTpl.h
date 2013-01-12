#pragma once
namespace engine
{
	class SkyLightTpl : public GameObjectTemplate
	{
	public:
		SkyLightTpl(GameObjectManagerPtr pManager, const std::wstring& name);
		virtual ~SkyLightTpl(void);

		GameObjectPtr					CreateGameObject();
		void							Release();
	};


}