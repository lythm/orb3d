#pragma once

#include "core\GameObjectComponent.h"
namespace engine
{

	class SoundEmitter : public GameObjectComponent
	{
	public:
		SoundEmitter(GameObjectManagerPtr pManager);
		virtual ~SoundEmitter(void);
	};



}