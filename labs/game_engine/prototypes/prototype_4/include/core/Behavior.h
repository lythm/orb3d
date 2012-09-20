#pragma once

#include "core\GameObjectComponent.h"

namespace engine
{
	namespace object_component
	{
		class Behavior : public GameObjectComponent
		{
		public:
			Behavior(void);
			virtual ~Behavior(void);
		};

	}
}
