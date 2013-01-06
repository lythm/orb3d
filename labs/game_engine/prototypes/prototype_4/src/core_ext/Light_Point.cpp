#include "core_ext_pch.h"
#include "..\..\include\core\ext\Light_Point.h"
#include "core\PointLight.h"
#include "core\RenderSystem.h"
#include "core\GameObject.h"
#include "package.h"

namespace engine
{
	Light_Point::Light_Point(GameObjectManagerPtr pManager) : GameObjectComponent(L"PointLight", pManager)
	{
	}


	Light_Point::~Light_Point(void)
	{
	}
	
	void Light_Point::Update()
	{
		if(m_pLight)
		{
			m_pLight->SetWorldTM(m_pObject->GetWorldTransform());
		}
	}
	
	PointLightPtr Light_Point::GetLight()
	{
		return m_pLight;
	}
	
	bool Light_Point::OnAttach()
	{
		m_pRS = m_pManager->GetRenderSystem();

		m_pLight = Package::GetAllocator()->AllocObject<PointLight>();
		m_pLight->Create(m_pRS->GetSysGraphics());

		m_pRS->AddLight(m_pLight);

		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));
		
		pPM->Begin(L"PointLight");
		{
			pPM->RegisterProperty<bool, PointLight>(m_pLight.get(), 
												L"Cast Shadow", 
												&PointLight::GetCastShadow,
												&PointLight::SetCastShadow);

			pPM->RegisterProperty<math::Color4, PointLight>(m_pLight.get(), 
												L"Diffuse Color", 
												&PointLight::GetDiffuseColor,
												&PointLight::SetDiffuseColor);

			
			pPM->RegisterProperty<float, PointLight>(m_pLight.get(), 
												L"Radius", 
												&PointLight::GetRadius,
												&PointLight::SetRadius);

			pPM->RegisterProperty<float, PointLight>(m_pLight.get(), 
												L"Fallout", 
												&PointLight::GetFallout,
												&PointLight::SetFallout);

			pPM->RegisterProperty<float, PointLight>(m_pLight.get(), 
				L"Intensity", 
				&PointLight::GetIntensity,
				&PointLight::SetIntensity);

			pPM->RegisterProperty<bool, PointLight>(m_pLight.get(), 
				L"Enabled", 
				&PointLight::GetEnabled,
				&PointLight::SetEnabled);

		}
		pPM->End();

		return true;
	}
	void Light_Point::OnDetach()
	{
		m_pRS->RemoveLight(m_pLight);
		m_pLight->Release();
		m_pLight.reset();
	}
}