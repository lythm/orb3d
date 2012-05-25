#pragma once

#include "network\Sys_Network.h"


namespace engine
{
	class ASIONetwork : public Sys_Network
	{
	public:
		ASIONetwork(void);
		virtual ~ASIONetwork(void);
	};


}