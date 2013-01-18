#pragma once



namespace ld3d
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
		void										Render(CameraPtr pCamera);
		void										Present();

		void										SetViewMatrix(const math::Matrix44& view);
		void										SetProjMatrix(const math::Matrix44& proj);

		const math::Matrix44&						GetViewMatrix();
		const math::Matrix44&						GetProjMatrix();
		
		Sys_GraphicsPtr								GetSysGraphics();

		void										SetClearColor(const math::Color4& clr);
		void										SetClearDepth(float d);
		void										SetClearStencil(int s);
		const math::Color4&							GetClearColor();
		void										ResizeFrameBuffer(int cx, int cy);

		void										SetSemanticsValue(RenderDataPtr pData);

		void										AddLight(LightPtr pLight);
		void										RemoveLight(LightPtr pLight);
		int											GetLightCount();

		RenderTargetPtr								GetGBuffer();
		RenderTargetPtr								GetABuffer();

		void										DrawFullScreenQuad(MaterialPtr pMaterial);

		const math::Color4&							GetGlobalAmbient();
		void										SetGlobalAmbient(const math::Color4& clr);

		RenderTargetPtr								CreateRenderTarget(int c, int w, int h, G_FORMAT format[]);
		void										SetRenderTarget(RenderTargetPtr pRT);
		void										ClearRenderTarget(RenderTargetPtr pRT, int index, const math::Color4 & clr);
		void										ClearDepthBuffer(DepthStencilBufferPtr pDS, CLEAR_DS_FLAG flag, float d, int s);

		int											GetFrameBufferWidth();
		int											GetFrameBufferHeight();

		MaterialPtr									CreateMaterialFromFile(const char* szFile);
		TexturePtr									CreateTextureFromFile(const char* szFile);

		void										AddPostEffect(PostEffectPtr pEffect);

		void										AddCamera(CameraPtr pCamera);
		void										RemoveCamera(CameraPtr pCamera);

	private:
		bool										CreateABuffer(int w, int h);
		bool										CreateGBuffer(int w, int h);

		void										DR_G_Pass();
		void										DR_Merge_Pass();
		void										DR_Light_Pass();
		void										RenderPostEffects();
		void										RenderFinal();
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

		RenderTargetPtr								m_pGBuffer;
		RenderTargetPtr								m_pABuffer;

		ScreenQuadPtr								m_pScreenQuad;

		LightManagerPtr								m_pLightManager;

		MaterialPtr									m_pLightMaterial;

		MaterialPtr									m_pScreenQuadMaterial;

		math::Color4								m_globalAmbientColor;

		PostEffectManagerPtr						m_pPostEffectManager;

		std::list<CameraPtr>						m_cameras;
	};
}
