#pragma once

#include "core/DataStream.h"

#include <fstream>

namespace ld3d
{
	class EXPORT_CLASS DataStream_File : public DataStream
	{
	public:
		enum
		{
			OPEN_READ		= 0x1,
			OPEN_WRITE		= 0x2,
			//OPEN_BINARY		= 0x4,
			//OPEN_TEXT		= 0x0,
		};
		DataStream_File(void);
		virtual ~DataStream_File(void);

		uint64								Write(void* buffer, uint64 bytes);
		uint64								Read(void* buffer, uint64 bytes);
		void								Seek(uint64 offset);
		void								Close();
		uint64								Size();
		uint64								Pos();


		bool								OpenStream(const wchar_t* szFile, bool read = true);
		bool								OpenStream(FILE* pFile);
	private:

		FILE*								m_pFile;

		uint64								m_oriPos;

	};

}