#pragma once

namespace orb
{
	struct DeviceId
	{
		enum 
		{
			device_network			= 0,
			device_mem				= 1,
			device_ipc				= 2,

			device_optional			= 255,
			device_guard			= device_optional + 2,
			device_packet_coder		= device_optional + 3,
			device_packet_filter	= device_optional + 4,
			device_logger			= device_optional + 5,
			device_event_logger		= device_optional + 6,
			device_sys_monitor		= device_optional + 7,
		};
	};

}
