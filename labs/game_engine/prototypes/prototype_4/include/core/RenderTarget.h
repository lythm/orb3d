#pragma once


namespace engine
{
	class RenderTarget
	{
	public:

		RenderTarget(void){}

		virtual ~RenderTarget(void){}

		virtual TexturePtr									AsTexture()							= 0;
		virtual void										Release()							= 0;

		virtual void										Clear(const math::Color4& clr)		= 0;

	};
}
