#include "core_pch.h"
#include "..\..\include\core\DirectionalLight.h"

namespace engine
{
	DirectionalLight::DirectionalLight(void) : Light(LT_DIRLIGHT)
	{
	}


	DirectionalLight::~DirectionalLight(void)
	{
	}
	void DirectionalLight::RenderLight(Sys_GraphicsPtr pGraphics)
	{

	}
}
