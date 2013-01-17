#pragma once

#include "core\CoreApi.h"
#include "core\Allocator.h"

namespace ld3d
{
	inline
		void*												mem_alloc(uint64 bytes)
	{
		return CoreApi::GetAllocator()->Alloc(bytes);
	}
	inline
		void												mem_free(void* pMem)
	{
		CoreApi::GetAllocator()->Free(pMem);
	}

	template<typename T> inline
		boost::shared_ptr<T>								alloc_object()
	{
		return CoreApi::GetAllocator()->AllocObject<T>();
	}

	template<typename T, typename TP> inline
		boost::shared_ptr<T>								alloc_object(TP p)
	{
		return CoreApi::GetAllocator()->AllocObject<T, TP>(p);
	}

	inline
		void												log(const std::wstring& text)
	{
		CoreApi::Log(text);
	}
}