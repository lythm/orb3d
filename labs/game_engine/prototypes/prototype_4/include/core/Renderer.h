#pragma once

namespace engine
{
	class Renderer
	{
	public:

		Renderer(void){}

		virtual ~Renderer(void){}


		virtual void								Render(Sys_GraphicsPtr pGraphics)				= 0;
	};

}
