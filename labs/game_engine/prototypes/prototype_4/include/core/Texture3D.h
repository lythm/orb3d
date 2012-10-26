#pragma once

#include "core\Texture.h"

namespace engine
{
	class Texture3D : public Texture
	{
	public:

		Texture3D(void){}

		virtual ~Texture3D(void){}

		TEXTURE_TYPE						GetType(){ return TEXTURE_3D; }
	};


}
