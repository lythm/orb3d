#pragma once

#include "core\GameObjectComponent.h"

namespace engine
{
	namespace object_component
	{
		class WorldMeshRenderer : public GameObjectComponent
		{
		public:
			WorldMeshRenderer(void);
			virtual ~WorldMeshRenderer(void);


			static WorldMeshRendererPtr					CreateComponent();
		};


	}
}