#pragma once
#include "core\Light.h"

namespace engine
{

	class EXPORT_CLASS SpotLight : public Light
	{
	public:
		SpotLight(void);
		virtual ~SpotLight(void);
	};

}