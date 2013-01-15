#include "core_pch.h"
#include "..\..\include\core\DataStream_Mem.h"
#include "core_utils.h"
namespace ld3d
{
	DataStream_Mem::DataStream_Mem(void)
	{
		m_pMem		= NULL;
		m_pos		= 0;
		m_size		= 0;
		m_bFreeMem	= true;
	}


	DataStream_Mem::~DataStream_Mem(void)
	{
	}
	uint64 DataStream_Mem::Write(void* buffer, uint64 bytes)
	{
		if(EnoughLeft(bytes) == false)
		{
			return 0;
		}

		memcpy(((uint8*)m_pMem) + m_pos, buffer, bytes);

		m_pos += bytes;

		return bytes;
	}
	uint64 DataStream_Mem::Read(void* buffer, uint64 bytes)
	{
		uint64 left = BytesLeft();

		if(left == 0)
		{
			return 0;
		}
		
		uint64 bytes_to_read = bytes <= left ? bytes : left;

		memcpy(buffer, ((uint8*)m_pMem) + m_pos, bytes_to_read);

		m_pos += bytes_to_read;

		return bytes_to_read;

	}

	void DataStream_Mem::Seek(uint64 offset)
	{
		if(offset <= m_size)
		{
			m_pos = offset;
		}
		else
		{
			m_pos = m_size;
		}
	}
	void DataStream_Mem::Close()
	{
		if(m_bFreeMem == true)
		{
			mem_free(m_pMem);
		}
		m_pMem = nullptr;
		m_pos = 0;
		m_size = 0;
		m_bFreeMem = true;

	}
	uint64 DataStream_Mem::Size()
	{
		return m_size;
	}
	uint64 DataStream_Mem::Pos()
	{
		return m_pos;
	}
	bool DataStream_Mem::OpenStream(void* pMem, uint64 bytes)
	{
		if(pMem == nullptr)
		{
			return false;
		}
		if(m_pMem != nullptr && m_pMem != pMem)
		{
			Close();
		}
		m_bFreeMem = false;
		m_pMem = pMem;
		m_size = bytes;
		m_pos = 0;
		
		return true;
	}
	bool DataStream_Mem::OpenStream(uint64 bytes)
	{
		if(bytes == 0)
		{
			return false;
		}
		if(m_pMem != nullptr)
		{
			Close();
		}

		m_pMem = mem_alloc(bytes);

		m_size = bytes;
		m_pos = 0;
		m_bFreeMem = true;

		return true;
	}
	bool DataStream_Mem::EnoughLeft(uint64 size)
	{
		//return (m_pos + size) <= m_size;

		return size <= BytesLeft();
	}
	uint64 DataStream_Mem::BytesLeft()
	{
		return m_size - m_pos;
	}
}