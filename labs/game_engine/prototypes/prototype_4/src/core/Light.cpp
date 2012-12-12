#include "core_pch.h"
#include "..\..\include\core\Light.h"

namespace engine
{

	Light::Light(LIGHT_TYPE type)
	{
		m_type = type;
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
}
