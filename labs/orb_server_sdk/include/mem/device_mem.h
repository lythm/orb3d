#pragma once

#include "types/orb_types.h"
#include "device/device_interface.h"
#include "device/device_list.h"

namespace orb
{
	namespace mem
	{
		class MemDevice : public Device
		{
		public:
			
			virtual void*											Alloc(uint32 bytes)				= 0;
			virtual void											Free(void* mem)					= 0;
			
		protected:
			MemDevice(): Device(DeviceId::device_mem){}
			virtual ~MemDevice(){}
		};
	}
}
