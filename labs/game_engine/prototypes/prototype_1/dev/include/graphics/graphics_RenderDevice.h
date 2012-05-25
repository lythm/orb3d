#pragma once
namespace graphics
{
	class RenderDevice
	{
	public:

		RenderDevice(void)
		{
		}

		virtual ~RenderDevice(void)
		{
		}

		virtual void							Render()					= 0;


	};

}
