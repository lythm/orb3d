#pragma once

#include "core\GameObjectComponent.h"

namespace engine
{
	namespace object_component
	{
		class Light : public GameObjectComponent
		{
		public:
			Light(void);
			virtual ~Light(void);
		};


	}
}
