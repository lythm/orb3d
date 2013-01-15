#pragma once

#include "core\PostEffect.h"

namespace ld3d
{
	class EXPORT_CLASS PostEffect_SSAO : public PostEffect
	{
	public:
		PostEffect_SSAO(void);
		virtual ~PostEffect_SSAO(void);

		
		void									Render(RenderSystemPtr pRenderer, RenderTargetPtr pInput, RenderTargetPtr pOutput);
		bool									Initialize(RenderSystemPtr pRS);
		void									Release();

		const float&							GetBias();
		const float&							GetIntensity();
		const float&							GetScale();
		const float&							GetSampleRad();
		const bool&								GetBlur();
		void									SetBlur(const bool& blur);
		void									SetBias(const float& bias);
		void									SetIntensity(const float& intensity);
		void									SetScale(const float& scale);
		void									SetSampleRad(const float& rad);

		
	private:
		MaterialPtr								m_pMaterial;
		MaterialPtr								m_pGBlurMaterial;

		TexturePtr								m_pSSAORandomTex;

		float									m_randomTexSize;
		float									m_sampleRad;
		float									m_intensity;
		float									m_scale;
		float									m_bias;
		bool									m_bBlur;
		RenderTargetPtr							m_pGBlurTarget;

	};
}
