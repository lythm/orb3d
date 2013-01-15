#pragma once

#include "core\Light.h"

namespace ld3d
{
	class EXPORT_CLASS DirectionalLight : public Light
	{
	public:
		DirectionalLight(void);
		virtual ~DirectionalLight(void);

		bool								Create(Sys_GraphicsPtr pGraphics);
		void								Release();
		void								RenderLight(RenderSystemPtr pRenderer);
	
	private:

		math::Vector3						m_dir;
		math::Color4						m_diff;

		MaterialPtr							m_pMaterial;
	};
}
