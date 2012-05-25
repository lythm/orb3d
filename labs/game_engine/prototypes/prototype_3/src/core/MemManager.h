#pragma once


#include <vector>


#ifndef CONTAINING_RECORD	
#define CONTAINING_RECORD(address, type, field) ((type *)( \
	(char *)(address) - \
	(ptrdiff_t)(&((type *)0)->field)))

#endif

namespace engine
{
	class MemManager
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



		struct Slot
		{
			uint64							blockBytes;
			MemSlot*						pSlot;
		};


	public:
		MemManager(void);
		virtual ~MemManager(void);

		bool								Initialize();
		void								Release();

		void*								Alloc(uint64 bytes);
		void								Free(void* mem);



	private:
		static bool slot_find(const Slot& s1, const Slot&s2);

	private:

		std::vector<Slot>							m_Slots;
	};


}
