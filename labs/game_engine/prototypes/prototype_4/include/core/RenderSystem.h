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

		bool									Initialize(Sys_GraphicsPtr pGraphics);
		void									Release();
		void									AddRenderData(RenderDataPtr pData);
		void									Clear();
		void									Render();
		void									Present();

		void									SetViewMatrix(const math::Matrix44& view);
		void									SetProjMatrix(const math::Matrix44& proj);

		Sys_GraphicsPtr							GetSysGraphics();

		void									SetClearColor(const math::Color4& clr);
		void									SetClearDepth(float d);
		void									SetClearStencil(int s);

		void									ResizeFrameBuffer(int cx, int cy);

		void									SetSemanticsValue(RenderDataPtr pData);

	private:
		bool									CreateGBuffer();
		void									RenderGBuffer();
		void									RenderScreenQuad();
	private:
		math::Matrix44							m_viewMatrix;
		math::Matrix44							m_projMatrix;
		std::vector<RenderDataPtr>				m_renderQueue;
		Sys_GraphicsPtr							m_pGraphics;

		math::Color4							m_clearClr;
		float									m_clearDepth;
		int										m_clearStencil;

		MultiRenderTargetPtr					m_pGBuffer;

		ScreenQuadPtr							m_pScreenQuad;

		MaterialPtr								m_pGBufferMaterial;
	};
}
