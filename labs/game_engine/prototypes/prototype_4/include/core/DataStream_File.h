#pragma once

#include "core/DataStream.h"

#include <fstream>

namespace engine
{
	class DataStream_File : public DataStream
	{
	public:
		enum
		{
			OPEN_BINARY,
			OPEN_TEXT,
		};
		DataStream_File(void);
		virtual ~DataStream_File(void);


		uint64								Read(void* buffer, uint64 bytes);
		void								Seek(uint64 offset);
		void								Close();
		uint64								Size();
		uint64								Pos();


		bool								Open(const wchar_t* szFile);
	private:

		FILE*								m_pFile;

	};

}