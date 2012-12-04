#pragma once


namespace engine
{
	class EXPORT_CLASS RenderSystem
	{
	public:
		RenderSystem(void);
		virtual ~RenderSystem(void);

		bool									Initialize(Sys_GraphicsPtr pGraphics);
		void									Release();
		void									AddRenderData(RenderDataPtr pData);
		void									Clear();
		void									Render();

		void									DR_Render();

		void									SetViewMatrix(const math::Matrix44& view);
		void									SetProjMatrix(const math::Matrix44& proj);

		Sys_GraphicsPtr							GetSysGraphics();

		void									SetClearColor(const math::Color4& clr);
		void									SetClearDepth(float d);
		void									SetClearStencil(int s);
	private:
		void									SetSemanticsValue(RenderDataPtr pData);
	private:
		math::Matrix44							m_viewMatrix;
		math::Matrix44							m_projMatrix;
		std::vector<RenderDataPtr>				m_renderQueue;
		Sys_GraphicsPtr							m_pGraphics;

		math::Color4							m_clearClr;
		float									m_clearDepth;
		int										m_clearStencil;
	};
}
