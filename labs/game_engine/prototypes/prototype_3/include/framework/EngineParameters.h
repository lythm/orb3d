#pragma once

#include <string>


namespace engine
{
	struct EngineParameters
	{
		void*						app_handle;
		std::string					config_file;
	};


}