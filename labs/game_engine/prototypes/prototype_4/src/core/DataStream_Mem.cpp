#include "core_pch.h"
#include "..\..\include\core\DataStream_Mem.h"
#include "core_utils.h"
namespace engine
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
	uint64 DataStream_Mem::Read(void* buffer, uint64 bytes)
	{
		if(EnoughToRead(bytes) == false)
		{
			return 0;
		}

		memcpy(buffer, ((uint8*)m_pMem) + m_pos, bytes);

		m_pos += bytes;

		return bytes;

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
	bool DataStream_Mem::EnoughToRead(uint64 size)
	{
		return (m_pos + size) <= m_size;
	}
}