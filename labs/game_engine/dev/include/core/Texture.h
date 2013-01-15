#pragma once

#include "g_format.h"

namespace engine
{
	class EXPORT_CLASS Texture
	{
	public:
		
		Texture(void){}
		virtual ~Texture(void){}

		virtual TEXTURE_TYPE								GetType()								= 0;

		virtual void										Release()								= 0;

	};
}
