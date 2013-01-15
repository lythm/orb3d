#pragma once

namespace ld3d
{
	class EXPORT_CLASS PostEffect
	{
	public:
		PostEffect(void);
		virtual ~PostEffect(void);

		virtual void									Render(RenderSystemPtr pRenderer, RenderTargetPtr pInput, RenderTargetPtr pOutput)						= 0;
		virtual void									Release()																								= 0;
	};
}
