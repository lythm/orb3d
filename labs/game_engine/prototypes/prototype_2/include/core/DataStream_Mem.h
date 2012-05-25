#pragma once
#include "core/DataStream.h"

namespace engine
{
	class DataStream_Mem : public DataStream
	{
	public:
		DataStream_Mem(void);
		virtual ~DataStream_Mem(void);

		uint64								Read(void* buffer, uint64 bytes);
		void								Seek(uint64 offset);
		void								Close();
		uint64								Size();
		uint64								Pos();

		bool								Open(void* data, uint64 bytes);

	private:
		uint8*								m_pBuffer;
		uint64								m_size;
		uint64								m_pos;
	};


}