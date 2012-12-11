#pragma once
#include "core\Light.h"

namespace engine
{
	class EXPORT_CLASS PointLight : public Light
	{
	public:
		PointLight(void);
		virtual ~PointLight(void);
	};
}

