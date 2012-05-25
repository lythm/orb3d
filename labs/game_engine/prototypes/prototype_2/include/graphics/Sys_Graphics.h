#pragma once


#include <graphics/GraphicsParameters.h>

namespace engine
{
	class Sys_Graphics
	{
	public:

		virtual bool								Initialize(const GraphicsParameters& param)				= 0;
		virtual void								Release()												= 0;
		virtual void								Render()												= 0;

		virtual void								SetClearColor(const math::Color4& clr)					= 0;

		virtual void								ClearRenderTarget()										= 0;
		virtual void								Present()												= 0;

		virtual void								PushRenderData(RenderDataPtr pData)						= 0;

		virtual void								SetRenderTarget(RenderTargetPtr pTarget)				= 0;


		virtual GeometryBufferPtr					CreateGeometryBuffer()									= 0;

		virtual GraphicsFXPtr						CreateGFX()												= 0;

		virtual FrameBufferPtr						GetFrameBuffer()										= 0;
	protected:

		Sys_Graphics(void)
		{
		}

		virtual ~Sys_Graphics(void)
		{
		}
	};


}
