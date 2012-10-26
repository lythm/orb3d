#pragma once

#include "core\Texture.h"


namespace engine
{
	class Texture2D : public Texture
	{
	public:

		Texture2D(void){}
		virtual ~Texture2D(void){}

		TEXTURE_TYPE						GetType(){ return TEXTURE_2D; }
	};


}
