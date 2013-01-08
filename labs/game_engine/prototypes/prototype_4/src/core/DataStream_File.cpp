#include "core_pch.h"
#include "..\..\include\core\DataStream_File.h"


namespace engine
{
	DataStream_File::DataStream_File(void)
	{
		m_pFile		= NULL;
		m_oriPos	= 0;
	}


	DataStream_File::~DataStream_File(void)
	{
	}
	uint64 DataStream_File::Read(void* buffer, uint64 bytes)
	{
		return fread(buffer, size_t(bytes), 1, m_pFile);
		
	}
	
	void DataStream_File::Seek(uint64 offset)
	{
		fseek(m_pFile, (long)offset + m_oriPos, SEEK_SET);

	}
	void DataStream_File::Close()
	{
		if(m_oriPos == 0)
		{
			fclose(m_pFile);
		}
		m_pFile = nullptr;
		m_oriPos = 0;

	}
	uint64 DataStream_File::Size()
	{
		uint64 pos = ftell(m_pFile);

		fseek(m_pFile, 0, SEEK_END);
		
		uint64 size = ftell(m_pFile);

		fseek(m_pFile, (long)pos, SEEK_SET);
		
		return size - m_oriPos;
	}
	uint64 DataStream_File::Pos()
	{
		return ftell(m_pFile) - m_oriPos;
	}
	bool DataStream_File::OpenStream(const wchar_t* szFile)
	{
		if(m_pFile != nullptr)
		{
			Close();
		}
		m_pFile = _wfopen(szFile, L"rb+");
		if(m_pFile == NULL)
		{
			return false;
		}

		m_oriPos = 0;

		return true;
	}
	bool DataStream_File::OpenStream(FILE* pFile)
	{
		if(pFile == nullptr)
		{
			return false;
		}
		if(m_pFile != nullptr && m_pFile != pFile)
		{
			Close();
		}

		m_pFile = pFile;

		m_oriPos = ftell(pFile);

		return true;
	}
}

