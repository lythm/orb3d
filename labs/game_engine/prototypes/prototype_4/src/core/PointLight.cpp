#include "core_pch.h"
#include "..\..\include\core\PointLight.h"

namespace engine
{
	PointLight::PointLight(void) : Light(LT_POINTLIGHT)
	{
		m_radius				= 1.0f;
		m_fallout				= 1.0f;
	}


	PointLight::~PointLight(void)
	{
	}
	float PointLight::GetRadius()
	{
		return m_radius;
	}
	void PointLight::SetRadius(float r)
	{
		m_radius = r;
	}

	float PointLight::GetFallout()
	{
		return m_fallout;
	}
	void PointLight::SetFallout(float f)
	{
		m_fallout = f;
	}
}