#pragma once


namespace engine
{
	class RenderSystem
	{
	public:
		RenderSystem(void);
		virtual ~RenderSystem(void);

		bool									Initialize(Sys_GraphicsPtr pGraphics);
		void									Release();
		void									AddRenderData(RenderDataPtr pData);
		void									Clear();
		void									Render();

	private:
		std::vector<RenderDataPtr>				m_renderQueue;
		Sys_GraphicsPtr							m_pGraphics;
	};
}
