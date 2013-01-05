#include "core_ext_pch.h"
#include "..\..\include\core\ext\Sky.h"

namespace engine
{
	Sky::Sky(GameObjectManagerPtr pManager) : GameObjectComponent(L"Sky", pManager)
	{
	}


	Sky::~Sky(void)
	{
	}
	bool Sky::OnAttach()
	{
		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"Sky");
		{
			

		}
		pPM->End();

		return true;
	}
	void Sky::OnDetach()
	{

	}
}
