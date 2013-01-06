#include "core_pch.h"
#include "..\..\include\core\DirectionalLight.h"
#include "core\Sys_Graphics.h"
#include "core\GPUBuffer.h"
#include "core\Material.h"
#include "core\RenderSystem.h"

namespace engine
{
	DirectionalLight::DirectionalLight(void) : Light(LT_DIRLIGHT)
	{
	}


	DirectionalLight::~DirectionalLight(void)
	{
	}
	
	bool DirectionalLight::Create(Sys_GraphicsPtr pGraphics)
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

		m_pMaterial = pGraphics->CreateMaterialFromFile("./assets/material/dr_render_directional_light.fx");

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
		if(m_pVB)
		{
			m_pVB->Release();
			m_pVB.reset();
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
		m_pMaterial->ApplyVertexFormat();
		
		Sys_GraphicsPtr pGraphics = pRenderer->GetSysGraphics();

		pGraphics->SetVertexBuffer(m_pVB, 0, sizeof(math::Vector3));
		pGraphics->SetPrimitiveType(PT_TRIANGLE_LIST);

		int nPass = 0;
		m_pMaterial->Begin(nPass);
		for(int i = 0; i < nPass; ++i)
		{
			m_pMaterial->ApplyPass(i);
			pGraphics->Draw(6, 0);
		}
		m_pMaterial->End();
	}
}
