#include "core_ext_pch.h"
#include "..\..\include\core\ext\Light_Dir.h"
#include "core\DirectionalLight.h"
#include "core\RenderSystem.h"
#include "core\GameObject.h"
#include "package.h"

namespace engine
{
	Light_Dir::Light_Dir(void) : GameObjectComponent(L"DirectionalLight")
	{
	}


	Light_Dir::~Light_Dir(void)
	{
	}
	Light_DirPtr Light_Dir::CreateComponent()
	{
		return Package::GetAllocator()->AllocObject<Light_Dir>();
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
	void Light_Dir::SetRenderSystem(RenderSystemPtr pRS)
	{
		m_pRS = pRS;
	}

	bool Light_Dir::OnAttach()
	{
		m_pLight = Package::GetAllocator()->AllocObject<DirectionalLight>();
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
