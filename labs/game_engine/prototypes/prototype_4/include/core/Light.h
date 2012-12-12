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

		LIGHT_TYPE								GetType() const;

	private:
		LIGHT_TYPE								m_type;

		LightPtr								m_pPrev;
		LightPtr								m_pNext;
	};
}