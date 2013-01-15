#pragma once

#include "core\DataStream.h"

namespace ld3d
{
	class EXPORT_CLASS DataStream_Mem
	{
	public:
		DataStream_Mem(void);
		virtual ~DataStream_Mem(void);

		uint64								Write(void* buffer, uint64 bytes);
		uint64								Read(void* buffer, uint64 bytes);
		void								Seek(uint64 offset);
		void								Close();
		uint64								Size();
		uint64								Pos();


		bool								OpenStream(void* pMem, uint64 bytes);
		bool								OpenStream(uint64 bytes);

	private:
		bool								EnoughLeft(uint64 size);
		uint64								BytesLeft();
	private:


		void*								m_pMem;
		uint64								m_pos;
		uint64								m_size;

		bool								m_bFreeMem;
	};


}