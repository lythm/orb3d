#pragma once


namespace ld3d
{
	class DepthStencilBuffer
	{
	public:

		DepthStencilBuffer(void){}
		virtual ~DepthStencilBuffer(void){}

		virtual void							Release()														= 0;
	};
}
