#include "core_pch.h"
#include "..\..\include\core\PoolAllocator.h"

namespace ld3d
{

	PoolAllocator::PoolAllocator(void)
	{
	}


	PoolAllocator::~PoolAllocator(void)
	{
	}
	void* PoolAllocator::Alloc(uint64 bytes)
	{
		return m_pMemPool->Alloc(bytes);
	}
	void PoolAllocator::Free(void* mem)
	{
		m_pMemPool->Free(mem);
	}
	bool PoolAllocator::Initialize()
	{
		m_pMemPool = MemPoolPtr(new MemPool);
		if(m_pMemPool->Initialize() == false)
		{
			return false;
		}
		return true;
	}
	void PoolAllocator::Release()
	{
		if(m_pMemPool)
		{
			m_pMemPool->Release();
			m_pMemPool.reset();
		}
	}
}