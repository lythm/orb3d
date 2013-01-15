#pragma once

#include "core\GameObjectComponent.h"

namespace engine
{

	class WorldMeshRenderer : public GameObjectComponent
	{
	public:
		WorldMeshRenderer(GameObjectManagerPtr pManager);
		virtual ~WorldMeshRenderer(void);


	};

}