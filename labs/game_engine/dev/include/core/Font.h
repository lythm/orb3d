#pragma once

namespace ld3d
{
	class Font
	{
	public:

		virtual void											DrawText(int x, int y, const char* szText)					= 0;

	protected:
		Font(void){}
		virtual ~Font(void){}
	};
}
