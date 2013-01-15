#pragma once

#include "core\GameObjectComponent.h"
namespace engine
{

	class SoundListener : public GameObjectComponent
	{
	public:
		SoundListener(GameObjectManagerPtr pManager);
		virtual ~SoundListener(void);
	};



}