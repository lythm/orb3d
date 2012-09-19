#pragma once

#include "core\GameObjectComponent.h"
namespace engine
{
	namespace object_component
	{
		class SoundListener : public GameObjectComponent
		{
		public:
			SoundListener(void);
			virtual ~SoundListener(void);
		};


	}
}