#include "core_pch.h"
#include "PostEffect_SSAO.h"
#include "core\RenderSystem.h"
#include "core\Material.h"
#include "core\Sys_Graphics.h"


namespace engine
{
	PostEffect_SSAO::PostEffect_SSAO(void)
	{
	}


	PostEffect_SSAO::~PostEffect_SSAO(void)
	{
	}
	bool PostEffect_SSAO::Initialize(RenderSystemPtr pRS)
	{
		m_pMaterial = pRS->GetSysGraphics()->CreateMaterialFromFile("./assets/material/dr_render_ssao.fx");

		VertexElement vf[] = 
		{
			VertexElement(0, VertexElement::POSITION,G_FORMAT_R32G32B32_FLOAT),
		};
		VertexFormat format;

		format.SetElement(vf, 1);

		m_pMaterial->SetVertexFormat(format);
		return true;
	}
	void PostEffect_SSAO::Release()
	{
		if(m_pMaterial)
		{
			m_pMaterial->Release();
			m_pMaterial.reset();
		}
	}

	void PostEffect_SSAO::Render(RenderSystemPtr pRenderer)
	{
		pRenderer->DrawFullScreenQuad(m_pMaterial);
	}
}
