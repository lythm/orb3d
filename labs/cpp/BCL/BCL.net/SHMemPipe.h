#pragma once

#include "bcl.h"

using namespace System;

namespace managed_bcl
{
	public ref class SHMemPipe
	{
	public:
		enum class Result
		{

			ret_ok,

			ret_failed,

			ret_buffer_overflow,

			ret_channel_closed,

			ret_timeout,

			ret_not_ready,

			ret_pipe_closed,

			ret_no_data,

		};

		SHMemPipe(void);
		virtual ~SHMemPipe();


		Result									Open(String^ pipeName, UInt32 readChannelBytes, UInt32 writeChannelBytes);


		Result									Attach(String^ pipeName);


		void									Close();
		
		bool									IsReady();

		
		Result									Write(array<Byte>^ buffer, int bytes);


		Result									Read(array<Byte>^ buffer, int% bytes);


	private:

		bcl::SHMemPipe*							m_pPipe;

	};


}