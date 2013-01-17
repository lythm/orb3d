#pragma once

#include "core\GameObjectComponent.h"

namespace ld3d
{
	class Camera : public GameObjectComponent
	{
	public:
		Camera(GameObjectManagerPtr pManager);
		virtual ~Camera(void);

		const Version&				GetVersion() const;
	};


}