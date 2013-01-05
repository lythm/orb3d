#include "core_pch.h"
#include "..\..\include\core\PointLight.h"
#include "core\MeshUtil.h"
#include "core\Sys_Graphics.h"
#include "core\GPUBuffer.h"
#include "core_utils.h"

namespace engine
{
	PointLight::PointLight(void) : Light(LT_POINTLIGHT)
	{
		m_radius				= 10.0f;
		m_fallout				= 1.0f;
		m_nVerts				= 0;
		m_modifiedWorldTM.MakeIdentity();

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
	bool PointLight::Create(Sys_GraphicsPtr pGraphics)
	{
		math::Vector3* pPos = MeshUtil::CreateSphere(1, 50, 50, m_nVerts);
		m_pVB = pGraphics->CreateBuffer(BT_VERTEX_BUFFER, m_nVerts * sizeof(math::Vector3), pPos, false);

		mem_free(pPos);

		if(m_pVB == GPUBufferPtr())
		{
			return false;
		}

		return true;
	}
	
	void PointLight::DrawLightVolumn(Sys_GraphicsPtr pGraphics)
	{
		pGraphics->SetVertexBuffer(m_pVB, 0, sizeof(math::Vector3));
		pGraphics->SetPrimitiveType(PT_TRIANGLE_LIST);

		pGraphics->Draw(m_nVerts, 0);
	}
	void PointLight::Release()
	{
		if(m_pVB)
		{
			m_pVB->Release();
			m_pVB.reset();
		}
	}
	const math::Matrix44& PointLight::GetWorldTM()
	{
		m_modifiedWorldTM = math::MatrixScale(math::Vector3(m_radius, m_radius, m_radius)) * Light::GetWorldTM();
		return m_modifiedWorldTM;
	}
}
