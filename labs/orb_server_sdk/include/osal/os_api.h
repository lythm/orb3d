#pragma once

#include "os_types.h"

namespace orb
{
	namespace os
	{
		
		_DLL_API uint64												get_tick();
		
		_DLL_API kernel_object										open_library(const w_char* lib);
		
		_DLL_API void*												load_func(kernel_object lib, const char* func);
		
		_DLL_API void												close_library(kernel_object lib);

	}
}
