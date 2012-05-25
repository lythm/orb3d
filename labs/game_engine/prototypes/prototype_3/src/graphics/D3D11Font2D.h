#pragma once


#include "graphics\Font2D.h"

namespace engine
{
	class D3D11Font2D : public Font2D
	{
	public:
		D3D11Font2D(void);
		virtual ~D3D11Font2D(void);
	};


}