#include "core_ext_pch.h"
#include "..\..\include\core\ext\Light_Sky.h"

#include "core\SkyLight.h"

#include "Package.h"
namespace engine
{

	Light_Sky::Light_Sky(void) : GameObjectComponent(L"SkyLight")
	{
	}


	Light_Sky::~Light_Sky(void)
	{
	}
	void Light_Sky::Update()
	{
		if(m_pLight)
		{
			m_pLight->SetWorldTM(m_pObject->GetWorldTransform());
		}
	}

	SkyLightPtr Light_Sky::GetLight()
	{
		return m_pLight;
	}
	void Light_Sky::SetRenderSystem(RenderSystemPtr pRS)
	{
		m_pRS = pRS;
	}

	bool Light_Sky::OnAttach()
	{
		m_pLight = Package::GetAllocator()->AllocObject<SkyLight>();
		m_pLight->Create(m_pRS->GetSysGraphics());

		m_pRS->AddLight(m_pLight);

		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"SkyLight");
		{
			pPM->RegisterProperty<bool, SkyLight>(m_pLight.get(), 
				L"Cast Shadow", 
				&SkyLight::GetCastShadow,
				&SkyLight::SetCastShadow);

			pPM->RegisterProperty<math::Color4, SkyLight>(m_pLight.get(), 
				L"Diffuse Color", 
				&SkyLight::GetDiffuseColor,
				&SkyLight::SetDiffuseColor);

		}
		pPM->End();

		return true;
	}
	void Light_Sky::OnDetach()
	{
		m_pRS->RemoveLight(m_pLight);
		m_pLight->Release();
		m_pLight.reset();
	}

}