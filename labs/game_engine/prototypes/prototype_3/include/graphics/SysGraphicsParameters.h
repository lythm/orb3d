#pragma once

#include <string>

namespace engine
{
	struct SysGraphicsParameters
	{
		void*						app_handle;
		std::wstring				module;

		uint32						width;
		uint32						height;
	};


}
