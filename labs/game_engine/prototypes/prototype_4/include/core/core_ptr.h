#pragma once

#include <boost\shared_ptr.hpp>
namespace engine
{
	class GameObject;
	class GameObjectManager;
	class GameObjectComponent;

	typedef boost::shared_ptr<GameObjectManager>			GameObjectManagerPtr;
	typedef boost::shared_ptr<GameObject>					GameObjectPtr;
	typedef boost::shared_ptr<GameObjectComponent>			GameObjectComponentPtr;

}
