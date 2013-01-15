#pragma once

#include "core\GameObjectComponent.h"
namespace ld3d
{

	class SoundListener : public GameObjectComponent
	{
	public:
		SoundListener(GameObjectManagerPtr pManager);
		virtual ~SoundListener(void);
	};



}