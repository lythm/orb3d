#pragma once
#include "core\viewfrustum.h"

namespace ld3d
{
	class LightManager
	{
	public:
		LightManager(void);
		virtual ~LightManager(void);

		bool									Initialize(RenderSystemPtr pRS);
		void									Release();

		void									AddLight(LightPtr pLight);
		void									RemoveLight(LightPtr pLight);
		int										GetLightCount();
		
		LightPtr								GetNextLight(LightPtr pLight);

		LightPtr								GetNextAffectingLight(LightPtr pLight, const ViewFrustum& frustum);

		void									RenderLights();
	private:

		LightPtr								m_pList;
		int										m_lightCount;
		Sys_GraphicsPtr							m_pGraphics;
		RenderSystemPtr							m_pRenderSystem;
	};
}
