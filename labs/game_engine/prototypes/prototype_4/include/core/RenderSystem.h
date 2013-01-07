#pragma once



namespace engine
{
	class EXPORT_CLASS RenderSystem : public boost::enable_shared_from_this<RenderSystem>
	{
		
		class ScreenQuad
		{
		public:
			
			bool									Init(Sys_GraphicsPtr pGraphics);
			void									Release();
			void									Render(Sys_GraphicsPtr pGraphics, MaterialPtr pMaterial);
		private:
			GPUBufferPtr							m_pVB;
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

		const math::Matrix44&						GetViewMatrix();
		const math::Matrix44&						GetProjMatrix();
		
		Sys_GraphicsPtr								GetSysGraphics();

		void										SetClearColor(const math::Color4& clr);
		void										SetClearDepth(float d);
		void										SetClearStencil(int s);

		void										ResizeFrameBuffer(int cx, int cy);

		void										SetSemanticsValue(RenderDataPtr pData);

		void										AddLight(LightPtr pLight);
		void										RemoveLight(LightPtr pLight);
		int											GetLightCount();

		MultiRenderTargetPtr						GetGBuffer();
		RenderTargetPtr								GetABuffer();

		void										DrawFullScreenQuad(MaterialPtr pMaterial);

		const math::Color4&							GetGlobalAmbient();
		void										SetGlobalAmbient(const math::Color4& clr);
	private:
		bool										CreateABuffer();
		bool										CreateGBuffer();

		void										DR_G_Pass();
		void										DR_Final_Pass();
		void										DR_Light_Pass();


		void										RenderForward();
		void										RenderShadowMaps();
		
	private:
		math::Matrix44								m_viewMatrix;
		math::Matrix44								m_projMatrix;

		std::vector<RenderDataPtr>					m_forwardQueue;
		std::vector<RenderDataPtr>					m_deferredQueue;
		std::vector<RenderDataPtr>					m_transparentQueue;
		
		Sys_GraphicsPtr								m_pGraphics;

		math::Color4								m_clearClr;
		float										m_clearDepth;
		int											m_clearStencil;

		MultiRenderTargetPtr						m_pGBuffer;
		
		RenderTargetPtr								m_pABuffer;

		ScreenQuadPtr								m_pScreenQuad;

		LightManagerPtr								m_pLightManager;

		MaterialPtr									m_pLightMaterial;

		MaterialPtr									m_pScreenQuadMaterial;

		math::Color4								m_globalAmbientColor;

	};
}
