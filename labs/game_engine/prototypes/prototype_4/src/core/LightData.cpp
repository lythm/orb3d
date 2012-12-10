#include "core_pch.h"
#include "..\..\include\core\LightData.h"
#include "core_utils.h"

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
	}
}
