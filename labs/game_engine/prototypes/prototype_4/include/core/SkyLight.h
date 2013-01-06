#pragma once

#include "core\Light.h"

namespace engine
{
	class EXPORT_CLASS SkyLight : public Light
	{
	public:
		SkyLight(void);
		virtual ~SkyLight(void);

		bool								Create(Sys_GraphicsPtr pGraphics);
		void								Release();
		void								RenderLight(RenderSystemPtr pRenderer);

	private:

		math::Vector3						m_dir;
		math::Color4						m_diff;

		GPUBufferPtr						m_pVB;
		MaterialPtr							m_pMaterial;
	};


}