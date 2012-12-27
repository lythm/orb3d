#pragma once

#include "core\GameObjectComponent.h"


namespace engine
{

	class MeshAnimator : public GameObjectComponent
	{
	public:
		MeshAnimator(GameObjectManagerPtr pManager);
		virtual ~MeshAnimator(void);
	};

}

