#pragma once

namespace orb
{
	namespace bcl
	{
		class _DLL_CLASS CircularQueue
		{
		public:

			enum Result
			{

				ret_ok,

				ret_buffer_overflow,

				ret_no_data,

				ret_not_enough_bytes,

			};


			CircularQueue(void* pBuffer, uint32 bufferBytes, bool deleteBuffer = false);

			CircularQueue(uint32 bufferBytes);

			~CircularQueue(void);

			void						Reset();

			Result						Write(void* pBuffer, uint32 bytes);

			Result						Read(void* pBuffer, uint32& bytes);

			Result						Peek(void* pBuffer, uint32 bytes);

			uint32						GetDataBytes();

			Result						Remove(uint32 bytes);

			void*						GetBuffer();

			void*						GetReadPtr();

			void*						GetWritePtr();

		private:

			uint32						m_dataBytes;

			uint32						m_bufferBytes;

			uint32						m_writePos;

			uint32						m_readPos;

			uint8*						m_pBuffer;

			bool						m_deleteBuffer;

		};


	}
}
