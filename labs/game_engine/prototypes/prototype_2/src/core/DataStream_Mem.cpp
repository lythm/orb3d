#include "core_pch.h"
#include "..\..\include\core\DataStream_Mem.h"


namespace engine
{
	DataStream_Mem::DataStream_Mem(void)
	{
		m_pBuffer			= NULL;
		m_size				= 0;
		m_pos				= 0;
	}


	DataStream_Mem::~DataStream_Mem(void)
	{
		Close();
	}
	uint64 DataStream_Mem::Read(void* buffer, uint64 bytes)
	{
		uint64 toread = m_size - m_pos;

		toread = bytes > toread ? toread : bytes;

		memcpy(buffer, m_pBuffer + m_pos, toread);

		m_pos += toread;

		return toread;
	}
	
	void DataStream_Mem::Seek(uint64 offset)
	{
		m_pos = offset;
	}
	void DataStream_Mem::Close()
	{
		delete m_pBuffer;
		m_pos = 0;
		m_size = 0;
		m_pBuffer = 0;
	}
	uint64 DataStream_Mem::Size()
	{
		return m_size;
	}
	uint64 DataStream_Mem::Pos()
	{
		return m_pos;
	}
	bool DataStream_Mem::Open(void* data, uint64 bytes)
	{

		m_pBuffer = (uint8*)data;
		m_size = bytes;
		m_pos = 0;

		return true;
	}
}