#pragma once


#ifndef CONTAINING_RECORD	
#define CONTAINING_RECORD(address, type, field) ((type *)( \
    (char *)(address) - \
    (ptrdiff_t)(&((type *)0)->field)))
#endif

namespace engine
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

	class MemManager
	{
	public:

		struct Slot
		{
			uint64									blockBytes;
			MemSlot*								pSlot;
		};

		MemManager(void);
		virtual ~MemManager(void);

		bool										Initialize();
		void										Release();

		void*										Alloc(uint64 bytes);
		void										Free(void* mem);


		template<typename T>
		boost::shared_ptr<T>							AllocObject()
		{
			T* pObj = (T*)Alloc(sizeof(T));
			
			return boost::shared_ptr<T>(new (pObj)T, boost::bind(&MemManager::FreeObject<T>, this, _1));
		}

	private:
		template<typename T>
		void										FreeObject(T* pObj)
		{
			pObj->~T();
			Free(pObj);
			
		}
		

	private:
		static bool slot_find(const Slot& s1, const Slot&s2);

	private:

		std::vector<Slot>							m_Slots;
	};
}

