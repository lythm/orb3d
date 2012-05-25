#pragma once

#include "bcl.h"
using namespace System;

namespace managed_bcl
{
	public ref class CircularQueue
	{
	public:
		enum class Result
		{

			ret_ok,

			ret_buffer_overflow,

			ret_no_data,

			ret_not_enough_bytes,
			
		};
		
		CircularQueue(int bufferBytes);


		virtual ~CircularQueue(void);

		void											Reset();


		Result											Write(array<Byte>^ buffer, int bytes);

		Result											Read(array<Byte>^ buffer, int % bytes);

		Result											Peek(array<Byte>^ buffer, int bytes);

		int												GetDataBytes();

		Result											Remove(int bytes);


		property int DataBytes
		{
			int get()
			{
				return m_pQueue->GetDataBytes();
			};
		};
		
	private:

		bcl::CircularQueue*								m_pQueue;
	};
}