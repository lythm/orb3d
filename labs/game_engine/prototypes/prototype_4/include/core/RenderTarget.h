#pragma once


namespace engine
{
	class RenderTarget
	{
	public:

		RenderTarget(void){}

		virtual ~RenderTarget(void){}


		virtual void SetColorBuffer(Texture2DPtr pTex)												= 0;
		virtual void SetDepthStencilBuffer(Texture2DPtr pTex)										= 0;

		

	};


}
