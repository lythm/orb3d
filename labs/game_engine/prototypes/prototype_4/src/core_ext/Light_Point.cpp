#include "core_ext_pch.h"
#include "..\..\include\core\ext\Light_Point.h"
#include "core\PointLight.h"
#include "core\RenderSystem.h"
#include "core\GameObject.h"
#include "package.h"

namespace engine
{
	Light_Point::Light_Point(void) : GameObjectComponent(L"PointLight")
	{
	}


	Light_Point::~Light_Point(void)
	{
	}
	Light_PointPtr Light_Point::CreateComponent()
	{
		return Package::GetAllocator()->AllocObject<Light_Point>();
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
	void Light_Point::SetRenderSystem(RenderSystemPtr pRS)
	{
		m_pRS = pRS;
	}

	bool Light_Point::OnAttach()
	{
		m_pLight = Package::GetAllocator()->AllocObject<PointLight>();
		//m_pLight->Init(m_pRS->GetSysGraphics());

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

			pPM->RegisterProperty<math::Color4, PointLight>(m_pLight.get(), 
												L"Ambient Color", 
												&PointLight::GetAmbientColor,
												&PointLight::SetAmbientColor);

			pPM->RegisterProperty<float, PointLight>(m_pLight.get(), 
												L"Radius", 
												&PointLight::GetRadius,
												&PointLight::SetRadius);

			pPM->RegisterProperty<float, PointLight>(m_pLight.get(), 
												L"Fallout", 
												&PointLight::GetFallout,
												&PointLight::SetFallout);

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