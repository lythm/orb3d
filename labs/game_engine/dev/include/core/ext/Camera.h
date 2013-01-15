#pragma once

#include "core\GameObjectComponent.h"

namespace engine
{
	class Camera : public GameObjectComponent
	{
	public:
		Camera(GameObjectManagerPtr pManager);
		virtual ~Camera(void);
	};


}