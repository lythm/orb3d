#pragma once


#include "core\GameObjectComponent.h"

namespace engine
{
	namespace object_component
	{
		class LuaBehavior :public GameObjectComponent
		{
		public:
			LuaBehavior(void);
			virtual ~LuaBehavior(void);
		};

	}
}