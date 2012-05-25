#pragma once

#include "types/orb_types.h"
#include "device/device_interface.h"
#include "device/device_list.h"

namespace orb
{
	namespace ipc
	{
		class IPCDevice : public Device
		{
		public:
			
			
			
		protected:
			IPCDevice(): Device(DeviceId::device_ipc){}
			virtual ~IPCDevice(){}
		};
	}
}
