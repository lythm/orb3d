#pragma once

#include "core\DataStream.h"

namespace engine
{
	class EXPORT_CLASS DataStream_Mem
	{
	public:
		DataStream_Mem(void);
		virtual ~DataStream_Mem(void);

		uint64								Read(void* buffer, uint64 bytes);
		void								Seek(uint64 offset);
		void								Close();
		uint64								Size();
		uint64								Pos();


		bool								OpenStream(void* pMem, uint64 bytes);
		bool								OpenStream(uint64 bytes);

	private:
		bool								EnoughToRead(uint64 size);
	private:


		void*								m_pMem;
		uint64								m_pos;
		uint64								m_size;

		bool								m_bFreeMem;
	};


}