#pragma once

namespace bcl
{
	class SHMemReturnValue
	{
	public:
		
		enum RetValue
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

	private:


		SHMemReturnValue(void);

		virtual ~SHMemReturnValue(void);

	};

}