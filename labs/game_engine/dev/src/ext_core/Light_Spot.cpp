#include "core_ext_pch.h"
#include "..\..\include\core\ext\Light_Spot.h"
#include "core\SpotLight.h"
#include "CorePackage.h"

namespace ld3d
{
	Light_Spot::Light_Spot(GameObjectManagerPtr pManager) : GameObjectComponent(L"SpotLight", pManager)
	{
	}


	Light_Spot::~Light_Spot(void)
	{
	}
	const Version& Light_Spot::GetVersion() const
	{
		return g_packageVersion;
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
	

	bool Light_Spot::OnAttach()
	{
		m_pRS = m_pManager->GetRenderSystem();
		m_pLight = m_pManager->GetAllocator()->AllocObject<SpotLight>();
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
												L"Intensity", 
												&SpotLight::GetIntensity,
												&SpotLight::SetIntensity);

			pPM->RegisterProperty<float, SpotLight>(m_pLight.get(), 
												L"Angle", 
												&SpotLight::GetAngle,
												&SpotLight::SetAngle);

			pPM->RegisterProperty<float, SpotLight>(m_pLight.get(), 
												L"Range", 
												&SpotLight::GetRange,
												&SpotLight::SetRange);

			pPM->RegisterProperty<bool, SpotLight>(m_pLight.get(), 
												L"Enabled", 
												&SpotLight::GetEnabled,
												&SpotLight::SetEnabled);
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
	bool Light_Spot::OnSerialize(DataStream* pStream)
	{
		bool bEnabled = m_pLight->GetEnabled();
		pStream->WriteBool(bEnabled);

		bool bCastShadow = m_pLight->GetCastShadow();
		pStream->WriteBool(bCastShadow);

		math::Color4 diff = m_pLight->GetDiffuseColor();
		pStream->Write(&diff, sizeof(diff));

		float intensity = m_pLight->GetIntensity();
		pStream->WriteFloat32(intensity);

		float angle = m_pLight->GetAngle();
		pStream->WriteFloat32(angle);

		float range = m_pLight->GetRange();
		pStream->WriteFloat32(range);

		return true;

	}
	bool Light_Spot::OnUnSerialize(DataStream* pStream, const Version& version)
	{
		if(version != GetVersion())
		{
			return false;
		}
		
		bool bEnabled = pStream->ReadBool();
		m_pLight->SetEnabled(bEnabled);

		bool bCastShadow = pStream->ReadBool();
		m_pLight->SetCastShadow(bCastShadow);

		math::Color4 diff;
		pStream->Read(&diff, sizeof(diff));
		m_pLight->SetDiffuseColor(diff);

		float intensity = pStream->ReadFloat32();
		m_pLight->SetIntensity(intensity);

		float angle = pStream->ReadFloat32();
		m_pLight->SetAngle(angle);

		float range = pStream->ReadFloat32();
		m_pLight->SetRange(range);

		return true;
		
	}
}
