#include "orb_bcl_pch.h"
#include "orb_bcl_CircularQueue.h"


namespace orb
{
	namespace bcl
	{
		CircularQueue::CircularQueue(void* pBuffer, uint32 bufferBytes, bool deleteBuffer)
		{

			m_dataBytes				= 0;

			m_bufferBytes			= bufferBytes;

			m_writePos				= 0;

			m_readPos				= 0;

			m_deleteBuffer			= deleteBuffer;

			m_pBuffer				= (uint8*)pBuffer;

		}
		CircularQueue::CircularQueue(uint32 bufferBytes)
		{

			m_dataBytes				= 0;

			m_bufferBytes			= bufferBytes;

			m_writePos				= 0;

			m_readPos				= 0;

			m_deleteBuffer			= true;

			m_pBuffer				= new uint8[bufferBytes];

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

		CircularQueue::Result CircularQueue::Write(void* pBuffer, uint32 bytes)
		{

			uint32 blankBytes					=  m_bufferBytes - m_dataBytes;


			// not enough room to write
			if(blankBytes < bytes)
			{

				return ret_buffer_overflow;

			}


			unsigned char* pos					= m_pBuffer + m_writePos;


			// bytes to the end of the buffer
			uint32 bytesToEnd					= m_bufferBytes - m_writePos;

			if(bytesToEnd >= bytes)
			{

				memcpy(pos, pBuffer, bytes);

				m_writePos						+= bytes;

				m_dataBytes						+= bytes;


				return ret_ok;

			}

			memcpy(pos, pBuffer, bytesToEnd);

			pos									= m_pBuffer;

			memcpy(pos, (uint8*)pBuffer + bytesToEnd, bytes - bytesToEnd);

			m_writePos							= bytes - bytesToEnd;

			m_dataBytes							+= bytes;

			return ret_ok;

		}

		CircularQueue::Result CircularQueue::Read(void* pBuffer, uint32& bytes)
		{

			if(m_dataBytes == 0)
			{

				return ret_no_data;

			}

			bytes								= (m_dataBytes >= bytes) ? bytes : m_dataBytes;
			uint8* pos							= m_pBuffer + m_readPos;

			uint32 bytesToEnd					= m_bufferBytes - m_readPos;

			if(bytesToEnd >= bytes)
			{

				memcpy(pBuffer, pos, bytes);

				m_readPos						+= bytes;

				m_dataBytes						-= bytes;

				return ret_ok;

			}


			memcpy(pBuffer, pos, bytesToEnd);

			pos									= m_pBuffer;

			memcpy((uint8*)pBuffer + bytesToEnd, pos, bytes - bytesToEnd);


			m_readPos							= bytes - bytesToEnd;


			m_dataBytes							-= bytes;


			return ret_ok;

		}
		uint32	CircularQueue::GetDataBytes()
		{

			return m_dataBytes;

		}
		CircularQueue::Result CircularQueue::Remove(uint32 bytes)
		{

			if(m_dataBytes < bytes)
			{

				return ret_not_enough_bytes;

			}

			uint32 bytesToEnd					= m_bufferBytes - m_readPos;

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
		CircularQueue::Result CircularQueue::Peek(void* pBuffer, uint32 bytes)
		{

			if(m_dataBytes < bytes)
			{
				return ret_not_enough_bytes;
			}

			uint8* pos							= m_pBuffer + m_readPos;

			uint32 bytesToEnd					= m_bufferBytes - m_readPos;

			if(bytesToEnd >= bytes)
			{
				memcpy(pBuffer, pos, bytes);

				return ret_ok;
			}


			memcpy(pBuffer, pos, bytesToEnd);

			pos									= m_pBuffer;

			memcpy((uint8*)pBuffer + bytesToEnd, pos, bytes - bytesToEnd);

			return ret_ok;

		}
		void CircularQueue::Reset()
		{
			m_dataBytes						= 0;

			m_writePos						= 0;

			m_readPos						= 0;

		}

	}
}
