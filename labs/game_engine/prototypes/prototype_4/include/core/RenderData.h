#pragma once


namespace engine
{
	class RenderData
	{
	public:

		RenderData(void){}

		virtual ~RenderData(void){}

		virtual void											Render(Sys_GraphicsPtr pSysGraphics)										= 0;


	};


}
