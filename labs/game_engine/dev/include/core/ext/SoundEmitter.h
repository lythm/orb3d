#pragma once

#include "core\GameObjectComponent.h"
namespace ld3d
{

	class SoundEmitter : public GameObjectComponent
	{
	public:
		SoundEmitter(GameObjectManagerPtr pManager);
		virtual ~SoundEmitter(void);
	};



}