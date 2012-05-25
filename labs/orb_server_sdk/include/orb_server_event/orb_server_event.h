#pragma once

#include "ede/ede_event.h"


namespace orb
{
	const uint64										SYS_EVENT_MASK		= 0xffff000000000000;
	const uint64										SM_EVENT_MASK		= 0x0001000000000000;
	const uint64										NET_EVENT_MASK		= 0x0002000000000000;


	struct BaseEvent : public ede::Event
	{

	};





}