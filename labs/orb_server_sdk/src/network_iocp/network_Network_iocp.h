#pragma once

#include "network/device_network.h"

namespace orb
{
	namespace network
	{

		class Network_iocp : public NetworkDevice
		{
		public:

			Network_iocp(void);

			virtual ~Network_iocp(void);

			const w_char*						GetName();

			bool								Initialize(DeviceHost* pHost);
			void								Release();

			Result								initialize_network(uint16 n_threads);

			void								release_network();

			Result								aio_read(aio_op* op);
			
			Result								aio_write(aio_op* op);

			Result								aio_disconnect(aio_op* op, bool reuse_sock);


			Result								aio_connect(aio_op* op, const IPAddress& addr);

			Result								aio_accept(sock listener_sock, aio_op* op);
			
			Result								aio_cancel(sock s);

			sock								socket();

			Result								bind(sock s, const IPAddress& addr);

			Result								listen(sock s);
			
			void								close(sock s);

		private:

			HANDLE								m_pIOCP;

			std::vector<HANDLE>					m_threads;
		private:


			static unsigned int __stdcall		iocp_handler(void* param);
		};

	}
}
