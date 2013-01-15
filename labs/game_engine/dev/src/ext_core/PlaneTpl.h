#pragma once

namespace ld3d
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