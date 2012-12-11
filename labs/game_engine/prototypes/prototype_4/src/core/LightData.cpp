#include "core_pch.h"
#include "..\..\include\core\LightData.h"
#include "core_utils.h"
#include "core_utils.h"
#include "core\PointLight.h"
#include "core\SpotLight.h"
#include "core\DirectionalLight.h"
#include "core\RenderSystem.h"

namespace engine
{
	namespace object_component
	{
		LightDataPtr LightData::CreateComponent()
		{
			return alloc_object<LightData>();
		}

		LightData::LightData(void) : GameObjectComponent(L"Light")
		{
		}
		
		LightData::~LightData(void)
		{
		}
		void LightData::Update()
		{

		}
		bool LightData::CreateLight(LIGHT_TYPE type)
		{
			switch(type)
			{
			case LT_DIRLIGHT:
				m_pLight = alloc_object<DirectionalLight>();
				
				break;
			case LT_SPOTLIGHT:
				m_pLight = alloc_object<SpotLight>();
				break;

			case LT_POINTLIGHT:
				m_pLight = alloc_object<PointLight>();
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
		bool LightData::OnAttach()
		{
			return true;
		}
		void LightData::OnDetach()
		{
			m_pRS->RemoveLight(m_pLight);
			m_pLight.reset();
		}
	}
}
