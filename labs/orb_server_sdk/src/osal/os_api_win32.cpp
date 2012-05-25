#include "os_api.h"

namespace orb
{
	namespace os
	{
		uint64 get_tick()
		{
			return GetTickCount();
		}

		kernel_object open_library(const w_char* lib)
		{
			SetErrorMode(SEM_FAILCRITICALERRORS);
			HANDLE hlib = LoadLibrary(lib);

			return (kernel_object)hlib;
		}
		

		void* load_func(kernel_object lib, const char* func)
		{
			return GetProcAddress((HMODULE)lib, func);
		}
		void close_library(kernel_object lib)
		{
			FreeLibrary((HMODULE)lib);
		}

	}
}
