#include "core_ext_pch.h"
#include "..\..\include\core\ext\Light_Point.h"
#include "core\PointLight.h"
#include "core\RenderSystem.h"
#include "core\GameObject.h"
#include "CorePackage.h"

namespace ld3d
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

		m_pLight = m_pManager->GetAllocator()->AllocObject<PointLight>();
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
	bool Light_Point::OnSerialize(DataStream* pStream)
	{
		bool bEnabled = m_pLight->GetEnabled();
		pStream->WriteBool(bEnabled);

		bool bCastShadow = m_pLight->GetCastShadow();
		pStream->WriteBool(bCastShadow);

		math::Color4 diff = m_pLight->GetDiffuseColor();
		pStream->Write(&diff, sizeof(diff));

		float intensity = m_pLight->GetIntensity();
		pStream->WriteFloat32(intensity);

		float radius = m_pLight->GetRadius();
		pStream->WriteFloat32(radius);
		return true;

	}
	bool Light_Point::OnUnSerialize(DataStream* pStream, const Version& version)
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

		float radius = pStream->ReadFloat32();
		m_pLight->SetRadius(radius);

		return true;
		
	}
	const Version& Light_Point::GetVersion() const
	{
		return g_packageVersion;
	}
}