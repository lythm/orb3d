#include "core_pch.h"
#include "..\..\include\core\DirectionalLight.h"
#include "core\Sys_Graphics.h"
#include "core\GPUBuffer.h"
#include "core\Material.h"
#include "core\RenderSystem.h"

namespace ld3d
{
	DirectionalLight::DirectionalLight(void) : Light(LT_DIRLIGHT)
	{
	}


	DirectionalLight::~DirectionalLight(void)
	{
	}
	
	bool DirectionalLight::Create(Sys_GraphicsPtr pGraphics)
	{
		m_pMaterial = pGraphics->CreateMaterialFromFile("./assets/standard/material/dr_render_directional_light.fx");

		VertexFormat vf;
		vf.AddElement(VertexElement(0, VertexElement::POSITION, G_FORMAT_R32G32B32_FLOAT));
		m_pMaterial->SetVertexFormat(vf);

		if(m_pMaterial == MaterialPtr())
		{
			return false;
		}
		return true;
	}
	void DirectionalLight::Release()
	{
		if(m_pMaterial)
		{
			m_pMaterial->Release();
			m_pMaterial.reset();
		}
	}
	void DirectionalLight::RenderLight(RenderSystemPtr pRenderer)
	{
		const math::Matrix44& view = pRenderer->GetViewMatrix();
		const math::Matrix44& proj = pRenderer->GetProjMatrix();


		m_pMaterial->SetWorldMatrix(math::MatrixIdentity());
		m_pMaterial->SetViewMatrix(view);
		m_pMaterial->SetProjMatrix(proj);


		const math::Matrix44& tm = GetWorldTM();

		math::Vector3 d = tm.GetRow3(2);
		d.Normalize();

		struct DirLightParam
		{
			math::Vector3 d;
			float i;
			math::Vector3 c;
			float specularPow;
		};

		DirLightParam l;
		l.d = d;
		l.i = GetIntensity();
		const math::Color4& diffClr = GetDiffuseColor();

		l.c = math::Vector3(diffClr.r, diffClr.g, diffClr.b);
		l.specularPow = GetSpecularPow();

		m_pMaterial->SetCBByName("light", &l, sizeof(DirLightParam));
		m_pMaterial->SetGBuffer(pRenderer->GetGBuffer());
				
		pRenderer->DrawFullScreenQuad(m_pMaterial);
	}
}
