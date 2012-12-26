#pragma once
#include "core\Light.h"

namespace engine
{
	class EXPORT_CLASS PointLight : public Light
	{
	public:
		PointLight(void);
		virtual ~PointLight(void);


		bool					Create(Sys_GraphicsPtr pGraphics);

		float					GetRadius();
		void					SetRadius(float r);

		float					GetFallout();
		void					SetFallout(float f);

		const math::Matrix44&	GetWorldTM();
		void					Release();
		void					DrawLightVolumn(Sys_GraphicsPtr pGraphics);

	private:
		float					m_radius;
		float					m_fallout;
		
		GPUBufferPtr			m_pVB;
		int						m_nVerts;

		math::Matrix44			m_modifedWorldTM;
	};
}
