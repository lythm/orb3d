#include "core_pch.h"
#include "..\..\include\core\DataStream_File.h"


namespace engine
{
	DataStream_File::DataStream_File(void)
	{
		m_pFile = NULL;
	}


	DataStream_File::~DataStream_File(void)
	{
	}
	uint64 DataStream_File::Read(void* buffer, uint64 bytes)
	{
		return fread(buffer, bytes, 1, m_pFile);
		
	}
	
	void DataStream_File::Seek(uint64 offset)
	{
		fseek(m_pFile, offset, SEEK_SET);

	}
	void DataStream_File::Close()
	{
		fclose(m_pFile);
	}
	uint64 DataStream_File::Size()
	{
		uint64 pos = ftell(m_pFile);

		fseek(m_pFile, 0, SEEK_END);
		
		uint64 size = ftell(m_pFile);

		fseek(m_pFile, pos, SEEK_SET);
		
		return size;
	}
	uint64 DataStream_File::Pos()
	{
		return ftell(m_pFile);
	}
	bool DataStream_File::Open(const wchar_t* szFile)
	{
		m_pFile = _wfopen(szFile, L"rb+");
		if(m_pFile == NULL)
		{
			return false;
		}

		return true;
	}
}
