#pragma once
#include "core\Light.h"

namespace ld3d
{

	class EXPORT_CLASS SpotLight : public Light
	{
	public:
		SpotLight(void);
		virtual ~SpotLight(void);

		bool							Create(Sys_GraphicsPtr pGraphics);
		const float&					GetAngle();
		void							SetAngle(const float& angle);

		const float&					GetRange();
		void							SetRange(const float& range);

		void							Release();
	
		void							RenderLight(RenderSystemPtr pRS);

	private:
		void							UpdateLightVolume();
	private:
		float							m_angle;
		float							m_range;

		GPUBufferPtr					m_pVB;
		int								m_nVerts;

		MaterialPtr						m_pMaterial;

		math::Matrix44					m_modifiedTM;

	};

}