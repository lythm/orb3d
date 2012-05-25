#pragma once


#include "graphics/graphics_RenderDevice.h"

namespace graphics
{
	class D3D11RenderDevice : public RenderDevice
	{
	public:
		D3D11RenderDevice(void);
		virtual ~D3D11RenderDevice(void);
	};
}
