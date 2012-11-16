#pragma once

namespace engine
{
	class MultiRenderTarget
	{
	public:

		MultiRenderTarget(void)
		{
		}

		virtual ~MultiRenderTarget(void)
		{
		}

		virtual void											Release()									= 0;
	};


}