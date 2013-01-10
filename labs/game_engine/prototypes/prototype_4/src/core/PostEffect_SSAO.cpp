#include "core_pch.h"
#include "PostEffect_SSAO.h"
#include "core\RenderSystem.h"
#include "core\Material.h"
#include "core\Sys_Graphics.h"
#include "core\Texture.h"
#include "core\RenderTarget.h"


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

		m_pSSAORandomTex = pRS->CreateTextureFromFile("./assets/texture/ssao_rand.jpg");
		
		m_pMaterial->SetTextureByName("tex_ssao_rand", m_pSSAORandomTex);
		return true;
	}
	void PostEffect_SSAO::Release()
	{
		if(m_pSSAORandomTex)
		{
			m_pSSAORandomTex->Release();
			m_pSSAORandomTex.reset();
		}
		if(m_pMaterial)
		{
			m_pMaterial->Release();
			m_pMaterial.reset();
		}
	}

	void PostEffect_SSAO::Render(RenderSystemPtr pRenderer, RenderTargetPtr pInput, RenderTargetPtr pOutput)
	{
		pRenderer->SetRenderTarget(pOutput);
		pRenderer->ClearRenderTarget(pOutput, 0, math::Color4(0, 0, 0,0));

		m_pMaterial->SetGBuffer(pRenderer->GetGBuffer());
		m_pMaterial->SetTextureByName("tex_input", pInput->AsTexture(0));
		m_pMaterial->SetVectorByName("g_screen_size", math::Vector2(pRenderer->GetFrameBufferWidth(), pRenderer->GetFrameBufferHeight()));

		pRenderer->DrawFullScreenQuad(m_pMaterial);
	}
}

