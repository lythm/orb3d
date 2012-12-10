#pragma once

#include "core\GameObjectComponent.h"

namespace engine
{
	namespace object_component
	{
		class LightData : public GameObjectComponent
		{
		public:
			LightData(void);
			virtual ~LightData(void);


			void										Update();
			static LightDataPtr							CreateComponent();


		};


	}
}
