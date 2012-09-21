#pragma once

#include "core\Sys_Graphics.h"


namespace engine
{
	class D3D11Graphics : public Sys_Graphics
	{
	public:
		D3D11Graphics(void);
		virtual ~D3D11Graphics(void);


		bool									Initialize(void* app_handle, uint32 width, uint32 height, uint32 format);
	};


}