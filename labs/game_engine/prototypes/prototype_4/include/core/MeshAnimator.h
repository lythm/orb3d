#pragma once

#include "core\GameObjectComponent.h"


namespace engine
{
	namespace object_component
	{
		class MeshAnimator : public GameObjectComponent
		{
		public:
			MeshAnimator(void);
			virtual ~MeshAnimator(void);
		};

	}
}