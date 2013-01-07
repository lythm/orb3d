#pragma once

namespace engine
{
	class PostEffect
	{
	public:
		PostEffect(void);
		virtual ~PostEffect(void);

		virtual void									Render(RenderSystemPtr pRenderer)						= 0;
	};
}