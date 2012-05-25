#include "os_api.h"

namespace orb
{
	namespace os
	{
		
		uint64 get_tick()
		{
			return 0;
		}

	
		kernel_object open_library(const w_char* lib)
		{
			return 0;
		}
		void* load_func(kernel_object lib, const char* func)
		{
			return 0;
		}
		void close_library(kernel_object lib)
		{
		}
	}
}
