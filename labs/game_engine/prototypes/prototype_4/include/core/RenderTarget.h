#pragma once


namespace engine
{
	class RenderTarget
	{
	public:

		virtual TexturePtr									AsTexture()														= 0;
		virtual void										Release()														= 0;
		virtual void										SetDepthStencilBuffer(DepthStencilBufferPtr pBuffer)			= 0;
		virtual DepthStencilBufferPtr						GetDepthStencilBuffer()											= 0;

	protected:
		RenderTarget(void){}

		virtual ~RenderTarget(void){}
	};
}
