#pragma once


namespace engine
{
	class DepthStencilBuffer
	{
	public:

		DepthStencilBuffer(void){}
		virtual ~DepthStencilBuffer(void){}

		virtual TexturePtr						AsTexture(G_FORMAT format = G_FORMAT_UNKNOWN)					= 0;
		virtual void							Release()														= 0;
		virtual void							Clear(float d, int s)											= 0;
	};
}
