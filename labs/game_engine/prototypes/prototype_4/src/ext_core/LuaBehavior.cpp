#include "core_ext_pch.h"
#include "..\..\include\core\ext\LuaBehavior.h"

namespace engine
{
	LuaBehavior::LuaBehavior(GameObjectManagerPtr pManager) : GameObjectComponent(L"LuaBehavior", pManager)
	{
	}


	LuaBehavior::~LuaBehavior(void)
	{
	}
	void LuaBehavior::Update()
	{
	}
	bool LuaBehavior::OnAttach()
	{
		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"LuaBehavior");
		{
			

		}
		pPM->End();

		return true;
	}
	void LuaBehavior::OnDetach()
	{
	}
}
