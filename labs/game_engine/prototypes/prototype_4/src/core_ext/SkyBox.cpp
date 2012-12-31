#include "core_ext_pch.h"
#include "..\..\include\core\ext\SkyBox.h"


namespace engine
{
	SkyBox::SkyBox(GameObjectManagerPtr pManager) : GameObjectComponent(L"SkyBox", pManager)
	{
	}


	SkyBox::~SkyBox(void)
	{
	}
	void SkyBox::Update()
	{
	}

	bool SkyBox::OnAttach()
	{
	
		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"SkyBox");
		{
		}
		pPM->End();

		return true;
	}
	void SkyBox::OnDetach()
	{
	}
}
