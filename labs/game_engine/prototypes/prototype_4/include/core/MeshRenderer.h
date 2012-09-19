#pragma once

#include "core\GameObjectComponent.h"


namespace engine
{
	namespace object_component
	{
		class MeshRenderer : public GameObjectComponent
		{
		public:
			MeshRenderer(void);
			virtual ~MeshRenderer(void);

			void							Update();
		};

	}
}
