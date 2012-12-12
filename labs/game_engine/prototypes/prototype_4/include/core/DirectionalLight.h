#pragma once

#include "core\Light.h"

namespace engine
{
	class EXPORT_CLASS DirectionalLight : public Light
	{
	public:
		DirectionalLight(void);
		virtual ~DirectionalLight(void);


		void								DrawLightVolumn(Sys_GraphicsPtr pGraphics);

	private:

		math::Vector3						m_dir;
		math::Color4						m_diff;

	};


}