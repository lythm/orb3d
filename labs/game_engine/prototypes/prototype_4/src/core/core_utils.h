#pragma once

#include "core\CoreApi.h"

namespace engine
{
	inline
		void*												mem_alloc(uint64 bytes)
	{
		return CoreApi::MemAlloc(bytes);
	}
	inline
		void												mem_free(void* pMem)
	{
		CoreApi::MemFree(pMem);
	}

	template<typename T> inline
		boost::shared_ptr<T>								alloc_object()
	{
		return CoreApi::AllocObject<T>();
	}

	template<typename T, typename TP> inline
		boost::shared_ptr<T>								alloc_object(TP p)
	{
		return CoreApi::AllocObject<T, TP>(p);
	}

}