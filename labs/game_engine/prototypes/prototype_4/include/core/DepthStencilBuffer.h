#pragma once


namespace engine
{
	class DepthStencilBuffer
	{
	public:

		DepthStencilBuffer(void){}
		virtual ~DepthStencilBuffer(void){}

		virtual TexturePtr						AsTexture()					= 0;
		virtual void							Release()					= 0;
	};
}