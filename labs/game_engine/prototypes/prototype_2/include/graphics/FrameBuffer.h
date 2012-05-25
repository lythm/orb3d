#pragma once

#include "graphics\RenderTarget.h"

namespace engine
{
	class FrameBuffer
	{
	public:

		virtual void									Release()											= 0;

		virtual void									Present()											= 0;

		virtual void									ClearColor()										= 0;
		virtual void									ClearDepthStencil()									= 0;
		virtual void									SetClearColor(const math::Color4& clr)				= 0;
		virtual void									SetDepthStencil(float depth, uint32 stencil)		= 0;

		virtual RenderTargetPtr							GetRenderTarget()									= 0;
	protected:

		FrameBuffer(void)
		{
		}

		virtual ~FrameBuffer(void)
		{
		}
	};
}
