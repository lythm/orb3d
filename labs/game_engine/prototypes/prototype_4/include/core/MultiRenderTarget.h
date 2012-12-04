#pragma once

namespace engine
{
	class MultiRenderTarget
	{
	public:

		virtual RenderTargetPtr									GetRenderTarget(int index)										= 0;
		virtual int												GetRenderTargetCount()											= 0;
		virtual TexturePtr										AsTexture(int index)											= 0;
		virtual void											SetDepthStencilBuffer(DepthStencilBufferPtr pDepthBuffer)		= 0;
		virtual DepthStencilBufferPtr							GetDepthStencilBuffer()											= 0;
		virtual void											Release()														= 0;

	protected:

		MultiRenderTarget(void){}
		virtual ~MultiRenderTarget(void){}
	};
}
