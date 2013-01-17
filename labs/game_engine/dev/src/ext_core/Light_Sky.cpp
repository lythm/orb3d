#include "core_ext_pch.h"
#include "..\..\include\core\ext\Light_Sky.h"

#include "core\SkyLight.h"

#include "CorePackage.h"
namespace ld3d
{

	Light_Sky::Light_Sky(GameObjectManagerPtr pManager) : GameObjectComponent(L"SkyLight", pManager)
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
	
	bool Light_Sky::OnAttach()
	{
		m_pRS = m_pManager->GetRenderSystem();
		m_pLight = m_pManager->GetAllocator()->AllocObject<SkyLight>();
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

			pPM->RegisterProperty<float, SkyLight>(m_pLight.get(), 
				L"Intensity", 
				&SkyLight::GetIntensity,
				&SkyLight::SetIntensity);

			pPM->RegisterProperty<float, SkyLight>(m_pLight.get(), 
				L"Specular Power", 
				&SkyLight::GetSpecularPow,
				&SkyLight::SetSpecularPow);
			pPM->RegisterProperty<bool, SkyLight>(m_pLight.get(), 
				L"Enabled", 
				&SkyLight::GetEnabled,
				&SkyLight::SetEnabled);

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
	bool Light_Sky::OnSerialize(DataStream* pStream)
	{
		bool bEnabled = m_pLight->GetEnabled();
		pStream->WriteBool(bEnabled);

		bool bCastShadow = m_pLight->GetCastShadow();
		pStream->WriteBool(bCastShadow);

		math::Color4 diff = m_pLight->GetDiffuseColor();
		pStream->Write(&diff, sizeof(diff));

		float intensity = m_pLight->GetIntensity();
		pStream->WriteFloat32(intensity);

		return true;

	}
	bool Light_Sky::OnUnSerialize(DataStream* pStream, const Version& version)
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

		return true;
		
	}
	const Version& Light_Sky::GetVersion() const
	{
		return g_packageVersion;
	}
}
