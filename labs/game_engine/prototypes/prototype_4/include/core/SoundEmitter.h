#pragma once

#include "core\GameObjectComponent.h"
namespace engine
{
	namespace object_component 
	{
		class SoundEmitter : public GameObjectComponent
		{
		public:
			SoundEmitter(void);
			virtual ~SoundEmitter(void);
		};


	}
}