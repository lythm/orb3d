#include "core_pch.h"
#include "..\..\include\core\DirectionalLight.h"
#include "core\Sys_Graphics.h"
#include "core\GPUBuffer.h"

namespace engine
{
	DirectionalLight::DirectionalLight(void) : Light(LT_DIRLIGHT)
	{
	}


	DirectionalLight::~DirectionalLight(void)
	{
	}
	void DirectionalLight::DrawLightVolumn(Sys_GraphicsPtr pGraphics)
	{
		pGraphics->SetVertexBuffer(m_pVB, 0, sizeof(math::Vector3));
		pGraphics->SetPrimitiveType(PT_TRIANGLE_LIST);

		pGraphics->Draw(6, 0);
	}
	bool DirectionalLight::Init(Sys_GraphicsPtr pGraphics)
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
	void DirectionalLight::Release()
	{
		if(m_pVB)
		{
			m_pVB->Release();
			m_pVB.reset();
		}
	}
}
