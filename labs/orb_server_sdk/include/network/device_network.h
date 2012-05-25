#pragma once

#include "device/device_interface.h"
#include "device/device_list.h"

namespace orb
{
	namespace network
	{

		class NetworkDevice : public Device
		{

		public:

			enum Result
			{

				ret_ok,

				ret_failed,

				ret_failed_to_load_wsock_ext,

				ret_failed_to_create_thread_pool,

				ret_bad_call,

			};


			virtual Result								aio_read(aio_op* op)												= 0;

			virtual Result								aio_write(aio_op* op)												= 0;

			virtual Result								aio_disconnect(aio_op* op, bool reuse_sock)							= 0;

			virtual Result								aio_connect(aio_op* op, const IPAddress& addr)						= 0;
			
			virtual Result								aio_accept(sock listener_sock, aio_op* op)							= 0;
			
			virtual Result								aio_cancel(sock s)													= 0;

			virtual sock								socket()															= 0;

			virtual Result								bind(sock s, const IPAddress& addr)									= 0;			

			virtual Result								listen(sock s)														= 0;
			
			virtual void								close(sock s)														= 0;


		protected:

			NetworkDevice(void):Device(DeviceId::device_network){}

			virtual ~NetworkDevice(void){}

		};

	}

}
