#include "mem_MemPool.h"

namespace orb
{
	namespace mem
	{
		_DLL_API Device* AllocDevice()
		{
			return new MemPool;
		}
		_DLL_API void FreeDevice(Device* pMem)
		{
			delete (MemPool*)pMem;
		}
	}
}


namespace orb
{
	namespace mem
	{
		MemPool::MemPool(void)
		{
		}


		MemPool::~MemPool(void)
		{
		}

		const w_char* MemPool::GetName()
		{
			return L"Pooled Memory Device";
		}
		void* MemPool::Alloc(uint32 bytes)
		{
			return malloc(bytes);
		}
		void MemPool::Free(void* mem)
		{
			free(mem);
		}
		void MemPool::Release()
		{
		}

		bool MemPool::Initialize(DeviceHost* pHost)
		{
			return true;
		}
	}
}
