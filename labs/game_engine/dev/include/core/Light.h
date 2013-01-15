#pragma once
#include <boost\enable_shared_from_this.hpp>

#include "core\ViewFrustum.h"

namespace ld3d
{
	class EXPORT_CLASS Light: public boost::enable_shared_from_this<Light>
	{
		friend class LightManager;

	public:
		
		Light(LIGHT_TYPE type);
		virtual ~Light(void);

		virtual void							RenderLight(RenderSystemPtr pRenderer);
		virtual void							Update();
		virtual void							RenderShadowMap();
		virtual bool							IsAffecting(const ViewFrustum& frustum);
		virtual void							Release();
		virtual const math::Matrix44&			GetWorldTM();
		virtual void							SetWorldTM(const math::Matrix44& world);

		LIGHT_TYPE								GetType() const;

		

		const math::Color4&						GetDiffuseColor();
		void									SetDiffuseColor(const math::Color4& clr);

		const bool&								GetCastShadow();
		void									SetCastShadow(const bool& bCast);

		const float&							GetSpecularPow();
		void									SetSpecularPow(const float& pow);

		const float&							GetIntensity();
		void									SetIntensity(const float& i);

		const bool&								GetEnabled();
		void									SetEnabled(const bool& bEnabled);
		
	protected:
		LIGHT_TYPE								m_type;

		LightPtr								m_pPrev;
		LightPtr								m_pNext;

		math::Matrix44							m_worldTM;

		bool									m_bCastShadow;
		math::Color4							m_diffClr;
		float									m_specularPow;
		float									m_intensity;

		bool									m_bEnabled;
	};
}
