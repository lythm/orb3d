#pragma once
#include "core\viewfrustum.h"

namespace engine
{
	class LightManager
	{
	public:
		LightManager(void);
		virtual ~LightManager(void);

		bool									Initialize(Sys_GraphicsPtr pGraphics);
		void									Release();

		void									AddLight(LightPtr pLight);
		void									RemoveLight(LightPtr pLight);
		int										GetLightCount();
		
		LightPtr								GetNextLight(LightPtr pLight);

		LightPtr								GetNextAffectingLight(LightPtr pLight, const ViewFrustum& frustum);

		MaterialPtr								GetLightMaterial();

		void									RenderLights(MultiRenderTargetPtr pGBuffer);
		void									RenderLight(MultiRenderTargetPtr pGBuffer, LightPtr pLight);
	private:

		LightPtr								m_pList;

		int										m_lightCount;

		MaterialPtr								m_pLightMaterial;

		Sys_GraphicsPtr							m_pGraphics;

	};
}
