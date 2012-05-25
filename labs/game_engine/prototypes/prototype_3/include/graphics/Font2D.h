#pragma once

namespace engine
{
	class Font2D
	{
	public:

		virtual void									Release()								= 0;
		virtual void									DrawText()								= 0;

	protected:
		Font2D(void){}

		virtual ~Font2D(void){}
	};


}
