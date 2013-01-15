#include "core_ext_pch.h"
#include "..\..\include\core\ext\Light_Dir.h"
#include "core\DirectionalLight.h"
#include "core\RenderSystem.h"
#include "core\GameObject.h"
#include "CorePackage.h"

namespace engine
{
	Light_Dir::Light_Dir(GameObjectManagerPtr pManager) : GameObjectComponent(L"DirectionalLight", pManager)
	{
	}


	Light_Dir::~Light_Dir(void)
	{
	}
	
	void Light_Dir::Update()
	{
		if(m_pLight)
		{
			m_pLight->SetWorldTM(m_pObject->GetWorldTransform());
		}
	}
	
	DirectionalLightPtr Light_Dir::GetLight()
	{
		return m_pLight;
	}
	bool Light_Dir::OnAttach()
	{
		m_pRS = m_pManager->GetRenderSystem();

		m_pLight = m_pManager->GetAllocator()->AllocObject<DirectionalLight>();
		m_pLight->Create(m_pRS->GetSysGraphics());

		m_pRS->AddLight(m_pLight);

		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));
		
		pPM->Begin(L"DirectionalLight");
		{
			pPM->RegisterProperty<bool, DirectionalLight>(m_pLight.get(), 
												L"Cast Shadow", 
												&DirectionalLight::GetCastShadow,
												&DirectionalLight::SetCastShadow);

			pPM->RegisterProperty<math::Color4, DirectionalLight>(m_pLight.get(), 
												L"Diffuse Color", 
												&DirectionalLight::GetDiffuseColor,
												&DirectionalLight::SetDiffuseColor);

			pPM->RegisterProperty<float, DirectionalLight>(m_pLight.get(), 
				L"Intensity", 
				&DirectionalLight::GetIntensity,
				&DirectionalLight::SetIntensity);

			pPM->RegisterProperty<float, DirectionalLight>(m_pLight.get(), 
				L"Specular Power", 
				&DirectionalLight::GetSpecularPow,
				&DirectionalLight::SetSpecularPow);

			pPM->RegisterProperty<bool, DirectionalLight>(m_pLight.get(), 
				L"Enabled", 
				&DirectionalLight::GetEnabled,
				&DirectionalLight::SetEnabled);

		}
		pPM->End();

		return true;
	}
	void Light_Dir::OnDetach()
	{
		m_pRS->RemoveLight(m_pLight);
		m_pLight->Release();
		m_pLight.reset();
	}

	
}
