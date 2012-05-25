#pragma once


#include "graphics\Texture.h"

namespace engine
{
	class D3D11Texture : public Texture
	{
	public:
		D3D11Texture(void);
		virtual ~D3D11Texture(void);
	};


}
