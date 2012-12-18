#pragma once

#include "core\Allocator.h"

namespace engine
{
	class EXPORT_CLASS StdAllocator : public Allocator
	{
	public:
		StdAllocator(void);
		virtual ~StdAllocator(void);

		void*								Alloc(uint64 bytes);
		void								Free(void* mem);
	};
}