#pragma once

#include "types/orb_types.h"
#include <WinSock2.h>
#include <mswsock.h>

namespace orb
{
	namespace network
	{
		struct _aio_op_private
		{
			OVERLAPPED				ol;
			WSABUF					buffer;
		};
	}
}
