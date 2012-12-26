#include "core_ext_pch.h"
#include "..\..\include\core\ext\Light_Spot.h"
#include "core\SpotLight.h"
#include "Package.h"

namespace engine
{
	Light_Spot::Light_Spot(void) : GameObjectComponent(L"SpotLight")
	{
	}


	Light_Spot::~Light_Spot(void)
	{
	}
	
	void Light_Spot::Update()
	{
		if(m_pLight)
		{
			m_pLight->SetWorldTM(m_pObject->GetWorldTransform());
		}
	}
	
	SpotLightPtr Light_Spot::GetLight()
	{
		return m_pLight;
	}
	void Light_Spot::SetRenderSystem(RenderSystemPtr pRS)
	{
		m_pRS = pRS;
	}

	bool Light_Spot::OnAttach()
	{
		m_pLight = Package::GetAllocator()->AllocObject<SpotLight>();
		m_pLight->Create(m_pRS->GetSysGraphics());
		m_pRS->AddLight(m_pLight);

		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));
		pPM->Begin(L"SpotLight");
		{
			pPM->RegisterProperty<bool, SpotLight>(m_pLight.get(), 
												L"Cast Shadow", 
												&SpotLight::GetCastShadow,
												&SpotLight::SetCastShadow);

			pPM->RegisterProperty<math::Color4, SpotLight>(m_pLight.get(), 
												L"Diffuse Color", 
												&SpotLight::GetDiffuseColor,
												&SpotLight::SetDiffuseColor);

			pPM->RegisterProperty<float, SpotLight>(m_pLight.get(), 
												L"Angle", 
												&SpotLight::GetAngle,
												&SpotLight::SetAngle);

			pPM->RegisterProperty<float, SpotLight>(m_pLight.get(), 
												L"Range", 
												&SpotLight::GetRange,
												&SpotLight::SetRange);
		}
		pPM->End();
		return true;
	}
	void Light_Spot::OnDetach()
	{
		m_pRS->RemoveLight(m_pLight);
		m_pLight->Release();
		m_pLight.reset();
	}
}
