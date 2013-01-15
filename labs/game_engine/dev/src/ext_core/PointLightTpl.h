#pragma once


namespace engine
{
	class PointLightTpl : public GameObjectTemplate
	{
	public:
		PointLightTpl(GameObjectManagerPtr pManager, const std::wstring& name);
		virtual ~PointLightTpl(void);

		GameObjectPtr					CreateGameObject();
		void							Release();
	};


}