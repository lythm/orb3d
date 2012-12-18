#pragma once

#include "core\Allocator.h"

namespace engine
{
	class StdAllocator : public Allocator
	{
	public:
		StdAllocator(void);
		virtual ~StdAllocator(void);

		void*								Alloc(uint64 bytes);
		void								Free(void* mem);
	};


}