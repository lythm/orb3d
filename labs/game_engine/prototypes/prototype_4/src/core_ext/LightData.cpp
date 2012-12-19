#include "core_ext_pch.h"
#include "..\..\include\core\ext\LightData.h"
#include "core\PointLight.h"
#include "core\SpotLight.h"
#include "core\DirectionalLight.h"
#include "core\RenderSystem.h"
#include "core\GameObject.h"
#include "package.h"
namespace engine
{

	LightDataPtr LightData::CreateComponent()
	{
		return Package::GetAllocator()->AllocObject<LightData>();
	}

	LightData::LightData(void) : GameObjectComponent(L"Light")
	{
	}

	LightData::~LightData(void)
	{
	}
	void LightData::Update()
	{
		if(m_pLight)
		{
			m_pLight->SetWorldTM(m_pObject->GetWorldTransform());
		}
	}
	bool LightData::CreateLight(LIGHT_TYPE type)
	{
		switch(type)
		{
		case LT_DIRLIGHT:
			m_pLight = Package::GetAllocator()->AllocObject<DirectionalLight>();
			((DirectionalLight*)m_pLight.get())->Init(m_pRS->GetSysGraphics());
			break;
		case LT_SPOTLIGHT:
			m_pLight = Package::GetAllocator()->AllocObject<SpotLight>();
			break;

		case LT_POINTLIGHT:
			m_pLight = Package::GetAllocator()->AllocObject<PointLight>();
			break;
		default:
			return false;
		}
		m_pRS->AddLight(m_pLight);
		return true;
	}
	LightPtr LightData::GetLight()
	{
		return m_pLight;
	}
	void LightData::SetRenderSystem(RenderSystemPtr pRS)
	{
		m_pRS = pRS;
	}
	void LightData::SetLightType(const int& t)
	{
		m_type = (LIGHT_TYPE)t;
	}
	const int& LightData::GetLightType()
	{
		return m_type;
	}
	bool LightData::OnAttach()
	{
		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));
		m_pPropSet = pPM->Begin(L"Light");


		pPM->RegisterProperty<int, LightData>(this, 
		L"LightType", 
		&LightData::GetLightType,
		&LightData::SetLightType);


		pPM->End();

		return true;
	}
	void LightData::OnDetach()
	{
		m_pRS->RemoveLight(m_pLight);
		m_pLight->Release();
		m_pLight.reset();
	}
}

