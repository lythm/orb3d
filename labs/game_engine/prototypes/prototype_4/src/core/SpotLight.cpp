#include "core_pch.h"
#include "..\..\include\core\SpotLight.h"

namespace engine
{
	SpotLight::SpotLight(void) : Light(LT_SPOTLIGHT)
	{
		m_angle			= 45;
	}


	SpotLight::~SpotLight(void)
	{
	}
	const float& SpotLight::GetAngle()
	{
		return m_angle;
	}
	void SpotLight::SetAngle(const float& angle)
	{
		m_angle = angle;
	}
}