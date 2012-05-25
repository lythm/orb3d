#pragma once

#include "mem/device_mem.h"

namespace orb
{
	namespace mem
	{
		class MemPool : public MemDevice
		{
		public:
			MemPool(void);
			virtual ~MemPool(void);

			const w_char*									GetName();

			void*											Alloc(uint32 bytes);
			void											Free(void* mem);

			bool											Initialize(DeviceHost* pHost);
			void											Release();

			
		};
	}
}
