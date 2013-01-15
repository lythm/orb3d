#include "core_pch.h"
#include "..\..\include\core\Light.h"

namespace ld3d
{

	Light::Light(LIGHT_TYPE type)
	{
		m_type = type;

		m_bCastShadow				= false;
		m_diffClr					= math::Color4(0.6f, 0.6f, 0.6f, 1.0f);

		m_specularPow				= 100;
		m_intensity					= 1;

		m_bEnabled					= true;
	}


	Light::~Light(void)
	{
	}
	void Light::Update()
	{
	}
	void Light::RenderShadowMap()
	{
	}
	LIGHT_TYPE Light::GetType() const
	{
		return m_type;
	}
	
	bool Light::IsAffecting(const ViewFrustum& frustum)
	{
		return true;
	}
	void Light::Release()
	{
	}
	const math::Matrix44& Light::GetWorldTM()
	{
		return m_worldTM;
	}
	void Light::SetWorldTM(const math::Matrix44& world)
	{
		m_worldTM = world;
	}
	const math::Color4& Light::GetDiffuseColor()
	{
		return m_diffClr;
	}
	void Light::SetDiffuseColor(const math::Color4& clr)
	{
		m_diffClr = clr;
	}
	
	const bool& Light::GetCastShadow()
	{
		return m_bCastShadow;
	}
	void Light::SetCastShadow(const bool& bCast)
	{
		m_bCastShadow = bCast;
	}
	const float& Light::GetSpecularPow()
	{
		return m_specularPow;
	}
	void Light::SetSpecularPow(const float& pow)
	{
		m_specularPow = pow;
	}
	const float& Light::GetIntensity()
	{
		return m_intensity;
	}
	void Light::SetIntensity(const float& i)
	{
		m_intensity = i > 1.0f ? 1.0f : i;
	}
	const bool&	Light::GetEnabled()
	{
		return m_bEnabled;
	}
	void Light::SetEnabled(const bool& bEnabled)
	{
		m_bEnabled = bEnabled;
	}
	void Light::RenderLight(RenderSystemPtr pRenderer)
	{

	}
}
