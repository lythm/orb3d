#pragma once

#include "core\Allocator.h"

namespace engine
{
	class EXPORT_CLASS PoolAllocator : public Allocator
	{
		typedef boost::shared_ptr<MemPool>				MemPoolPtr;
	public:
		PoolAllocator(void);
		virtual ~PoolAllocator(void);

		void*											Alloc(uint64 bytes);
		void											Free(void* mem);

		bool											Initialize();
		void											Release();
	private:
		MemPoolPtr										m_pMemPool;
	};


}