#include "core_ext_pch.h"
#include "..\..\include\core\ext\PostEffectList.h"


namespace engine
{

	PostEffectList::PostEffectList(GameObjectManagerPtr pManager) : GameObjectComponent(L"PostEffectList", pManager)
	{
	}


	PostEffectList::~PostEffectList(void)
	{
	}
	bool PostEffectList::OnAttach()
	{
		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"PostEffectList");
		{
			

		}
		pPM->End();

		return true;
	}
	void PostEffectList::OnDetach()
	{

	}
}
