#pragma once

#include "types/orb_types.h"

#ifdef _WIN32
#include "network_types_iocp.h"

#elif __FreeBSD__
#include "network_types_kq.h"

#else

#endif

#include "network_address.h"

namespace orb
{
	namespace network
	{
		typedef	uint64	sock;

		const sock invalid_sock						= sock(-1);

		struct aio_op;

		typedef void (*aio_completion_handler)(aio_op*);

		struct aio_op
		{
			enum op_code
			{
				op_accept,
				op_read,
				op_write,
				op_connect,
				op_disconnect,

			};
			
			enum op_result
			{
				result_ok,
				result_failed,
				result_abort,
			};

			_aio_op_private				_private_data;

			sock						s;
			op_code						op;
			op_result					result;
			uint32						sock_error;
					
			uint8*						buffer;
			uint32						buffer_bytes;
			uint32						data_transfered;


			aio_completion_handler		handler;
		};
	}
}
