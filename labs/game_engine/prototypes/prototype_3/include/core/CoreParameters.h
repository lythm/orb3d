#pragma once


#include "input\SysInputParameters.h"
#include "graphics\SysGraphicsParameters.h"

namespace engine
{
	struct CoreParameters
	{
		SysInputParameters							input;
		SysGraphicsParameters						graphics;
	};
}