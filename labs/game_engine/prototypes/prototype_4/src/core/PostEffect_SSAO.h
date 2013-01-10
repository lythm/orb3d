#pragma once

#include "core\PostEffect.h"

namespace engine
{
	class PostEffect_SSAO : public PostEffect
	{
	public:
		PostEffect_SSAO(void);
		virtual ~PostEffect_SSAO(void);

		void									Render(RenderSystemPtr pRenderer);

		bool									Initialize(RenderSystemPtr pRS);
		void									Release();

	private:
		MaterialPtr								m_pMaterial;
	};
}