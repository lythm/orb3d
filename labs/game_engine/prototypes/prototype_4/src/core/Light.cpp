#include "core_pch.h"
#include "..\..\include\core\Light.h"

namespace engine
{

	Light::Light(LIGHT_TYPE type)
	{
		m_type = type;

		m_bCastShadow				= false;
		m_diffClr					= math::Color4(1, 1, 1, 1);
		m_ambClr					= math::Color4(0, 0, 0, 1);
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
	void Light::DrawLightVolumn(Sys_GraphicsPtr pGraphics)
	{

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
	const math::Color4& Light::GetAmbientColor()
	{
		return m_ambClr;
	}
	void Light::SetAmbientColor(const math::Color4& clr)
	{
		m_ambClr = clr;
	}
	bool Light::GetCastShadow()
	{
		return m_bCastShadow;
	}
	void Light::SetCastShadow(bool bCast)
	{
		m_bCastShadow = bCast;
	}
}
