#include "core_pch.h"
#include "..\..\include\core\SpotLight.h"
#include "core\MeshUtil.h"
#include "core\GPUBuffer.h"
#include "core\Sys_Graphics.h"

namespace engine
{
	SpotLight::SpotLight(void) : Light(LT_SPOTLIGHT)
	{
		m_angle			= 45;
		m_nVerts		= 0;
		m_range			= 10;
	}


	SpotLight::~SpotLight(void)
	{
	}
	bool SpotLight::Create(Sys_GraphicsPtr pGraphics)
	{
		m_pVB = MeshUtil::CreateSpotLightCone(pGraphics, m_range, m_angle, 50, m_nVerts);
		if(m_pVB == GPUBufferPtr())
		{
			return false;
		}
		return true;
	}
	const float& SpotLight::GetAngle()
	{
		return m_angle;
	}
	void SpotLight::SetAngle(const float& angle)
	{
		m_angle = angle;
	}
	const float& SpotLight::GetRange()
	{
		return m_range;
	}
	void SpotLight::SetRange(const float& range)
	{
		m_range = range;
	}
	void SpotLight::DrawLightVolumn(Sys_GraphicsPtr pGraphics)
	{
		pGraphics->SetVertexBuffer(m_pVB, 0, sizeof(math::Vector3));
		pGraphics->SetPrimitiveType(PT_TRIANGLE_LIST);

		pGraphics->Draw(m_nVerts, 0);
	}
	void SpotLight::Release()
	{
		if(m_pVB)
		{
			m_pVB->Release();
			m_pVB.reset();
		}
	}
}
