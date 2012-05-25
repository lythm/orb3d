#pragma once

namespace bcl
{
	class DLL_EXPORT CircularQueue
	{
	public:

		enum Result
		{

			ret_ok,

			ret_buffer_overflow,

			ret_no_data,

			ret_not_enough_bytes,
			
		};


		CircularQueue(unsigned char* pBuffer, int bufferBytes, bool deleteBuffer = false);

		CircularQueue(int bufferBytes);
		
		~CircularQueue(void);

		void						Reset();

		Result						Write(void* pBuffer, int bytes);

		Result						Read(void* pBuffer, int& bytes);

		Result						Peek(void* pBuffer, int bytes);

		int							GetDataBytes();

		Result						Remove(int bytes);
		
		void*						GetBuffer();

		void*						GetReadPtr();

		void*						GetWritePtr();

	private:

		int							m_dataBytes;

		int							m_bufferBytes;

		int							m_writePos;

		int							m_readPos;

		unsigned char*				m_pBuffer;
		
		bool						m_deleteBuffer;

	};
}
