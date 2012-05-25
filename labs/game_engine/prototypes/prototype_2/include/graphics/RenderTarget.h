#pragma once


namespace engine
{
	class RenderTarget
	{
	public:
		virtual void											Release()							= 0;

	protected:

		RenderTarget(void)
		{
		}

		virtual ~RenderTarget(void)
		{
		}
	};


}