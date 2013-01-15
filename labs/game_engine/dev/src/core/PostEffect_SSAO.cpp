#include "core_pch.h"
#include "core\PostEffect_SSAO.h"
#include "core\RenderSystem.h"
#include "core\Material.h"
#include "core\Sys_Graphics.h"
#include "core\Texture.h"
#include "core\RenderTarget.h"


namespace ld3d
{
	PostEffect_SSAO::PostEffect_SSAO(void)
	{
		m_randomTexSize				= 64;
		m_sampleRad					= 2;
		m_intensity					= 2;
		m_scale						= 3;
		m_bias						= cosf(math::D2R(70));
		m_bBlur						= true;
	}


	PostEffect_SSAO::~PostEffect_SSAO(void)
	{
	}
	bool PostEffect_SSAO::Initialize(RenderSystemPtr pRS)
	{
		
		m_pMaterial = pRS->CreateMaterialFromFile("./assets/standard/material/dr_render_ssao.fx");

		VertexElement vf[] = 
		{
			VertexElement(0, VertexElement::POSITION,G_FORMAT_R32G32B32_FLOAT),
		};
		VertexFormat format;

		format.SetElement(vf, 1);

		m_pMaterial->SetVertexFormat(format);

		m_pSSAORandomTex = pRS->CreateTextureFromFile("./assets/standard/texture/ssao_rand.jpg");
		
		m_pMaterial->SetTextureByName("tex_ssao_rand", m_pSSAORandomTex);


		int w = pRS->GetFrameBufferWidth();

		int h = pRS->GetFrameBufferHeight();
		G_FORMAT rt_format[1] = {G_FORMAT_R8G8B8A8_UNORM,};
		m_pGBlurTarget = pRS->CreateRenderTarget(1, w , h , rt_format);

		if(m_pGBlurTarget == nullptr)
		{
			return false;
		}

		m_pGBlurMaterial = pRS->CreateMaterialFromFile("./assets/standard/material/dr_render_BBlur.fx");

		if(m_pGBlurMaterial == nullptr)
		{
			return false;
		}
		
		m_pGBlurMaterial->SetVertexFormat(format);
		return true;
	}
	void PostEffect_SSAO::Release()
	{
		if(m_pGBlurTarget)
		{
			m_pGBlurTarget->Release();
			m_pGBlurTarget.reset();
		}
		if(m_pGBlurMaterial)
		{
			m_pGBlurMaterial->Release();
			m_pGBlurMaterial.reset();
		}
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
		pRenderer->SetRenderTarget(m_pGBlurTarget);
		pRenderer->ClearRenderTarget(m_pGBlurTarget, 0, math::Color4(0, 0, 0,0));

		m_pMaterial->SetGBuffer(pRenderer->GetGBuffer());
		m_pMaterial->SetVectorByName("g_screen_size", math::Vector2(pRenderer->GetFrameBufferWidth(), pRenderer->GetFrameBufferHeight()));

		m_pMaterial->SetFloatByName("g_scale", m_scale);
		m_pMaterial->SetFloatByName("g_random_size", m_randomTexSize);
		m_pMaterial->SetFloatByName("g_sample_rad", m_sampleRad);
		m_pMaterial->SetFloatByName("g_bias", m_bias);
		m_pMaterial->SetFloatByName("g_intensity", m_intensity);


		pRenderer->DrawFullScreenQuad(m_pMaterial);

		pRenderer->SetRenderTarget(pOutput);
		pRenderer->ClearRenderTarget(pOutput, 0, math::Color4(0, 0, 0,0));
		
		m_pGBlurMaterial->SetGBuffer(pRenderer->GetGBuffer());
		m_pGBlurMaterial->SetTextureByName("tex_ao", m_pGBlurTarget->AsTexture(0));
		m_pGBlurMaterial->SetVectorByName("g_input_size", math::Vector2(pRenderer->GetFrameBufferWidth(), pRenderer->GetFrameBufferHeight()));
		m_pGBlurMaterial->SetTextureByName("tex_input", pInput->AsTexture(0));
		pRenderer->DrawFullScreenQuad(m_pGBlurMaterial);
	}
	const float& PostEffect_SSAO::GetBias()
	{
		return m_bias;
	}
	const float& PostEffect_SSAO::GetIntensity()
	{
		return m_intensity;
	}
	const float& PostEffect_SSAO::GetScale()
	{
		return m_scale;
	}
	const float& PostEffect_SSAO::GetSampleRad()
	{
		return m_sampleRad;
	}

	void PostEffect_SSAO::SetBias(const float& bias)
	{
		m_bias = bias;
	}
	void PostEffect_SSAO::SetIntensity(const float& intensity)
	{
		m_intensity = intensity;
	}
	void PostEffect_SSAO::SetScale(const float& scale)
	{
		m_scale = scale;
	}
	void PostEffect_SSAO::SetSampleRad(const float& rad)
	{
		m_sampleRad = rad;
	}
	const bool&	PostEffect_SSAO::GetBlur()
	{
		return m_bBlur;
	}
	void PostEffect_SSAO::SetBlur(const bool& blur)
	{
		m_bBlur = blur;
	}
}

