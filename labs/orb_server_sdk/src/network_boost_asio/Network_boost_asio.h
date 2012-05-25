#pragma once

#include "network_types.h"
#include "network/device_network.h"

namespace orb
{
	namespace network
	{
		class Network_boost_asio : public NetworkDevice
		{
		public:
			Network_boost_asio(void);
			virtual ~Network_boost_asio(void);
		};


	}
}

