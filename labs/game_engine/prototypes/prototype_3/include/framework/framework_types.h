#pragma once


#include <boost\smart_ptr.hpp>

namespace engine
{
	class GameEngine;
	class GameManager;

	class EngineMain;
	class EngineConfig;

	class GameObject;
	class GameObjectComponent;



	typedef boost::shared_ptr<GameObject>						GameObjectPtr;
	typedef boost::shared_ptr<GameObjectComponent>				GameObjectComponentPtr;
	typedef boost::shared_ptr<EngineConfig>						EngineConfigPtr;
	typedef boost::shared_ptr<EngineMain>						EngineMainPtr;
	typedef boost::shared_ptr<GameManager>						GameManagerPtr;
	typedef boost::shared_ptr<GameEngine>						GameEnginePtr;

}