#pragma once

#include "ipc/device_ipc.h"

namespace orb
{
	namespace ipc
	{

		class IPC_Boost : public IPCDevice
		{
		public:
			IPC_Boost(void);
			virtual ~IPC_Boost(void);
		};


	}
}
