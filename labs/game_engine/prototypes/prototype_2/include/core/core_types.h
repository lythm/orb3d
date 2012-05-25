#pragma once
#include <boost/shared_ptr.hpp>

#include "graphics\graphics_types.h"

namespace engine
{
	class Event;
	class EventDispatcher;
	class EventManager;
	class SysManager;
	class SceneManager;
	class UIManager;
	class MemManager;


	typedef boost::shared_ptr<MemManager>							MemManagerPtr;
	typedef boost::shared_ptr<UIManager>							UIManagerPtr;
	typedef boost::shared_ptr<SceneManager>							SceneManagerPtr;
	typedef boost::shared_ptr<SysManager>							SysManagerPtr;
	typedef boost::shared_ptr<Event>								EventPtr;
	typedef boost::shared_ptr<EventDispatcher>						EventDispatcherPtr;
	typedef boost::shared_ptr<EventManager>							EventManagerPtr;



	class Sys_Graphics;
	class Sys_Input;
	class Sys_Sound;
	class Sys_Network;

	typedef boost::shared_ptr<Sys_Network>							Sys_NetworkPtr;
	typedef boost::shared_ptr<Sys_Sound>							Sys_SoundPtr;
	typedef boost::shared_ptr<Sys_Graphics>							Sys_GraphicsPtr;
	typedef boost::shared_ptr<Sys_Input>							Sys_InputPtr;


	class AssetsManager;
	class Model;
	class Mesh;
	class DataStream;

	typedef boost::shared_ptr<DataStream>							DataStreamPtr;
	typedef boost::shared_ptr<AssetsManager>						AssetsManagerPtr;
	typedef boost::shared_ptr<Model>								ModelPtr;
	typedef boost::shared_ptr<Mesh>									MeshPtr;

}
