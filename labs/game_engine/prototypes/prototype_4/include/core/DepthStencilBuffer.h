#pragma once


namespace engine
{
	class DepthStencilBuffer
	{
	public:

		DepthStencilBuffer(void){}
		virtual ~DepthStencilBuffer(void){}

		virtual void							Release()														= 0;
		virtual void							Clear(float d, int s)											= 0;
	};
}
