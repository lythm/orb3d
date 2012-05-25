#pragma once

#include "graphics\graphics_types.h"

namespace engine
{
	class SysGraphics;
	class SysInput;
	class SysManager;
	class EngineCore;
	class MemManager;

	class GameObject;
	class GameObjectComponent;
	class GameObjectManager;


	typedef boost::shared_ptr<GameObjectManager>			GameObjectManagerPtr;
	typedef boost::shared_ptr<MemManager>					MemManagerPtr;
	typedef boost::shared_ptr<GameObject>					GameObjectPtr;
	typedef boost::shared_ptr<GameObjectComponent>			GameObjectComponentPtr;

	typedef boost::shared_ptr<SysManager>					SysManagerPtr;
	typedef boost::shared_ptr<EngineCore>					EngineCorePtr;
	typedef boost::shared_ptr<SysGraphics>					SysGraphicsPtr;
	typedef boost::shared_ptr<SysInput>						SysInputPtr;

}