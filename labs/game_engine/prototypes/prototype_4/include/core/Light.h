#pragma once
#include <boost\enable_shared_from_this.hpp>

#include "core\ViewFrustum.h"

namespace engine
{
	class EXPORT_CLASS Light: public boost::enable_shared_from_this<Light>
	{
		friend class LightManager;

	public:
		
		Light(LIGHT_TYPE type);
		virtual ~Light(void);

		virtual void							DrawLightVolumn(Sys_GraphicsPtr pGraphics);
		virtual void							Update();
		virtual void							RenderShadowMap();
		virtual bool							IsAffecting(const ViewFrustum& frustum);
		virtual void							Release();


		LIGHT_TYPE								GetType() const;

		const math::Matrix44&					GetWorldTM();
		void									SetWorldTM(const math::Matrix44& world);

		const math::Color4&						GetDiffuseColor();
		void									SetDiffuseColor(const math::Color4& clr);

		bool									GetCastShadow();
		void									SetCastShadow(bool bCast);

	private:
		LIGHT_TYPE								m_type;

		LightPtr								m_pPrev;
		LightPtr								m_pNext;

		math::Matrix44							m_worldTM;

		bool									m_bCastShadow;
		math::Color4							m_diffClr;
	};
}
