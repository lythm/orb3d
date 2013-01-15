#pragma once

#include "types\types.h"
#include <vector>
#include <boost\function.hpp>
#include <boost\bind.hpp>



namespace ld3d
{

	class MemSlot
	{
	public:

		struct _MemNode
		{
			_MemNode*					next;
			uint64						bytes;
			uint8						data[];
		};

		MemSlot();
		virtual ~MemSlot();


		bool							Init(uint64 blockBytes);
		void							Release();

		void*							Alloc(uint64 bytes);
		void							Free(void* pData);

		uint64							GetBlockBytes();

	private:

		uint64							m_blockBytes;
		uint64							m_totalBytes;

		_MemNode*						m_pHead;


		int64							m_blockCount;

		uint64							m_allocCount;
		uint64							m_freeCount;
	};

	class MemPool
	{
	public:

		struct Slot
		{
			uint64									blockBytes;
			MemSlot*								pSlot;
		};

		MemPool(void);
		virtual ~MemPool(void);

		bool										Initialize();
		void										Release();

		void*										Alloc(uint64 bytes);
		void										Free(void* mem);


		template<typename T>
		boost::shared_ptr<T>						AllocObject()
		{
			T* pObj = (T*)Alloc(sizeof(T));
			
			return boost::shared_ptr<T>(new (pObj)T, boost::bind(&MemPool::FreeObject<T>, this, _1));
		}
		template<typename T, typename TP>
		boost::shared_ptr<T>						AllocObject(TP param)
		{
			T* pObj = (T*)Alloc(sizeof(T));
			
			return boost::shared_ptr<T>(new (pObj) T(param), boost::bind(&MemPool::FreeObject<T>, this, _1));
		}

	private:
		template<typename T>
		void										FreeObject(T* pObj)
		{
			pObj->~T();
			Free(pObj);
		}
		
		void										WarmSlot(uint64 bytes, int count);

	private:
		static bool slot_find(const Slot& s1, const Slot&s2);

	private:

		std::vector<Slot>							m_Slots;
	};
}

