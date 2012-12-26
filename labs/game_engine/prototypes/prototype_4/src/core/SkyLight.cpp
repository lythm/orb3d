#include "core_pch.h"
#include "..\..\include\core\SkyLight.h"
#include "core\Sys_Graphics.h"
#include "core\GPUBuffer.h"

namespace engine
{
	SkyLight::SkyLight(void) : Light(LT_SKYLIGHT)
	{
	}


	SkyLight::~SkyLight(void)
	{
	}
	void SkyLight::DrawLightVolumn(Sys_GraphicsPtr pGraphics)
	{
		pGraphics->SetVertexBuffer(m_pVB, 0, sizeof(math::Vector3));
		pGraphics->SetPrimitiveType(PT_TRIANGLE_LIST);

		pGraphics->Draw(6, 0);
	}
	bool SkyLight::Create(Sys_GraphicsPtr pGraphics)
	{
		math::Vector3 verts[] = 
		{
			math::Vector3(-1, 1, 0),
			math::Vector3(1, 1, 0),
			math::Vector3(1, -1, 0),
			math::Vector3(-1, 1, 0),
			math::Vector3(1, -1, 0),
			math::Vector3(-1, -1, 0),
		};

		m_pVB = pGraphics->CreateBuffer(BT_VERTEX_BUFFER, sizeof(math::Vector3) * 6, verts, true);


		return true;
	}
	void SkyLight::Release()
	{
		if(m_pVB)
		{
			m_pVB->Release();
			m_pVB.reset();
		}
	}
}