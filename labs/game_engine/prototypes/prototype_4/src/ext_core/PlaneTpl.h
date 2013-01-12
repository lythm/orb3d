#pragma once

namespace engine
{
	class PlaneTpl : public GameObjectTemplate
	{
	public:
		PlaneTpl(GameObjectManagerPtr pManager, const std::wstring& name);
		virtual ~PlaneTpl(void);

		GameObjectPtr					CreateGameObject();
		void							Release();
	};


}