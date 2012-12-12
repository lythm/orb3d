#pragma once


namespace engine
{
	class EXPORT_CLASS RenderSystem
	{
		
		class ScreenQuad
		{
		public:
			
			bool									Init(Sys_GraphicsPtr pGraphics);
			void									Release();
			void									Render(Sys_GraphicsPtr pGraphics, MultiRenderTargetPtr pGBuffer);
			MaterialPtr								GetMaterial();
		private:
			GPUBufferPtr							m_pVB;
			MaterialPtr								m_pMaterial;
		};

		typedef boost::shared_ptr<ScreenQuad>		ScreenQuadPtr;
	public:
		RenderSystem(void);
		virtual ~RenderSystem(void);

		bool										Initialize(Sys_GraphicsPtr pGraphics);
		void										Release();
		void										AddRenderData(RenderDataPtr pData);
		void										Clear();
		void										Render();
		void										Present();

		void										SetViewMatrix(const math::Matrix44& view);
		void										SetProjMatrix(const math::Matrix44& proj);

		Sys_GraphicsPtr								GetSysGraphics();

		void										SetClearColor(const math::Color4& clr);
		void										SetClearDepth(float d);
		void										SetClearStencil(int s);

		void										ResizeFrameBuffer(int cx, int cy);

		void										SetSemanticsValue(RenderDataPtr pData);

		void										AddLight(LightPtr pLight);
		void										RemoveLight(LightPtr pLight);
		int											GetLightCount();
	private:
		bool										CreateABuffer();
		bool										CreateGBuffer();
		void										RenderGBuffer();
		void										RenderScreenQuad();
		void										RenderForward();
		void										RenderLight(LightPtr pLight);
		void										RenderLights();
		void										RenderShadowMaps();
		void										MergeOutput();

	private:
		math::Matrix44								m_viewMatrix;
		math::Matrix44								m_projMatrix;

		std::vector<RenderDataPtr>					m_forwardQueue;
		std::vector<RenderDataPtr>					m_deferredQueue;
		
		Sys_GraphicsPtr								m_pGraphics;

		math::Color4								m_clearClr;
		float										m_clearDepth;
		int											m_clearStencil;

		MultiRenderTargetPtr						m_pGBuffer;
		
		RenderTargetPtr								m_pABuffer;

		ScreenQuadPtr								m_pScreenQuad;

		LightManagerPtr								m_pLightManager;

		MaterialPtr									m_pLightMaterial;

	};
}
