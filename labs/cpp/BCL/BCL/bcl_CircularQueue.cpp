#include "bcl_types.h"
#include "..\include\bcl_CircularQueue.h"

namespace bcl
{
	CircularQueue::CircularQueue(unsigned char* pBuffer, int bufferBytes, bool deleteBuffer)
	{

		m_dataBytes				= 0;

		m_bufferBytes			= bufferBytes;

		m_writePos				= 0;

		m_readPos				= 0;

		m_deleteBuffer			= deleteBuffer;

		m_pBuffer				= pBuffer;

	}
	CircularQueue::CircularQueue(int bufferBytes)
	{

		m_dataBytes				= 0;

		m_bufferBytes			= bufferBytes;

		m_writePos				= 0;

		m_readPos				= 0;

		m_deleteBuffer			= true;

		m_pBuffer				= new unsigned char[bufferBytes];

	}


	CircularQueue::~CircularQueue(void)
	{

		if(m_deleteBuffer && m_pBuffer)
		{

			delete []m_pBuffer;

		}

		m_dataBytes				= 0;

		m_bufferBytes			= 0;

		m_writePos				= 0;

		m_readPos				= 0;

		m_deleteBuffer			= false;

	}

	CircularQueue::Result CircularQueue::Write(void* pBuffer, int bytes)
	{

		DWORD blankBytes					=  m_bufferBytes - m_dataBytes;
		

		// not enough room to write
		if(blankBytes < bytes)
		{

			return ret_buffer_overflow;

		}
		

		unsigned char* pos					= m_pBuffer + m_writePos;
		
		
		// bytes to the end of the buffer
		DWORD bytesToEnd					= m_bufferBytes - m_writePos;

		if(bytesToEnd >= bytes)
		{

			memcpy_s(pos, bytesToEnd, pBuffer, bytes);

			m_writePos						+= bytes;

			m_dataBytes						+= bytes;


			return ret_ok;

		}

		memcpy_s(pos, bytesToEnd, pBuffer, bytesToEnd);

		pos									= m_pBuffer;

		memcpy(pos, (unsigned char*)pBuffer + bytesToEnd, bytes - bytesToEnd);

		m_writePos							= bytes - bytesToEnd;

		m_dataBytes							+= bytes;
				
		return ret_ok;

	}

	CircularQueue::Result CircularQueue::Read(void* pBuffer, int& bytes)
	{

		if(m_dataBytes == 0)
		{

			return ret_no_data;

		}

		bytes								= (m_dataBytes >= bytes) ? bytes : m_dataBytes;
		
		BYTE* pos							= m_pBuffer + m_readPos;

		DWORD bytesToEnd					= m_bufferBytes - m_readPos;

		if(bytesToEnd >= bytes)
		{

			memcpy_s(pBuffer, bytes, pos, bytes);

			m_readPos						+= bytes;

			m_dataBytes						-= bytes;

			return ret_ok;

		}


		memcpy_s(pBuffer, bytes, pos, bytesToEnd);

		pos									= m_pBuffer;

		memcpy((BYTE*)pBuffer + bytesToEnd, pos, bytes - bytesToEnd);


		m_readPos							= bytes - bytesToEnd;

		
		m_dataBytes							-= bytes;
		

		return ret_ok;

	}
	int	CircularQueue::GetDataBytes()
	{

		return m_dataBytes;

	}
	CircularQueue::Result CircularQueue::Remove(int bytes)
	{

		if(m_dataBytes < bytes)
		{

			return ret_not_enough_bytes;

		}

		DWORD bytesToEnd					= m_bufferBytes - m_readPos;

		if(bytesToEnd >= bytes)
		{

			m_readPos						+= bytes;

			m_dataBytes						-= bytes;

			return ret_ok;
		}

		m_readPos							= bytes - bytesToEnd;

		
		m_dataBytes							-= bytes;
		
		return ret_ok;

	}
		
	void* CircularQueue::GetBuffer()
	{

		return m_pBuffer;

	}

	void* CircularQueue::GetReadPtr()
	{

		return m_pBuffer + m_readPos;

	}

	void* CircularQueue::GetWritePtr()
	{

		return m_pBuffer + m_writePos;

	}
	CircularQueue::Result CircularQueue::Peek(void* pBuffer, int bytes)
	{

		if(m_dataBytes < bytes)
		{
			return ret_not_enough_bytes;
		}

		BYTE* pos							= m_pBuffer + m_readPos;

		DWORD bytesToEnd					= m_bufferBytes - m_readPos;

		if(bytesToEnd >= bytes)
		{
			memcpy_s(pBuffer, bytes, pos, bytes);

			return ret_ok;
		}


		memcpy_s(pBuffer, bytes, pos, bytesToEnd);

		pos									= m_pBuffer;

		memcpy((BYTE*)pBuffer + bytesToEnd, pos, bytes - bytesToEnd);

		return ret_ok;

	}
	void CircularQueue::Reset()
	{
		m_dataBytes						= 0;

		m_writePos						= 0;

		m_readPos						= 0;

	}
}
