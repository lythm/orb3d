#pragma once
#include "core\Light.h"

namespace ld3d
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
		void					RenderLight(RenderSystemPtr pRS);

	private:
		void					DrawLightVolumn(RenderSystemPtr pRS);
		void					DrawQuad(RenderSystemPtr pRS);
	private:
		float					m_radius;
		float					m_fallout;
		
		GPUBufferPtr			m_pVB;
		int						m_nVerts;

		math::Matrix44			m_modifiedWorldTM;

		MaterialPtr				m_pMaterial;
	};
}
