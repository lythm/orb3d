#pragma once

#include "core\Texture.h"

namespace engine
{
	class Texture1D : public Texture
	{
	public:

		Texture1D(void){}

		virtual ~Texture1D(void){}

		TEXTURE_TYPE						GetType(){ return TEXTURE_1D; }
	};


}