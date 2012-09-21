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



	class Sys_Input;
	class Sys_Graphics;
	class Sys_Sound;
	class Sys_Physics;
	class SysManager;


	typedef boost::shared_ptr<SysManager>					SysManagerPtr;

	typedef boost::shared_ptr<Sys_Physics>					Sys_PhysicsPtr;
	typedef boost::shared_ptr<Sys_Input>					Sys_InputPtr;
	typedef boost::shared_ptr<Sys_Graphics>					Sys_GraphicsPtr;
	typedef boost::shared_ptr<Sys_Sound>					Sys_SoundPtr;

	class Mesh;

	typedef boost::shared_ptr<Mesh>							MeshPtr;


	class RenderData;
	class Texture;
	class GFX;

	typedef boost::shared_ptr<RenderData>					RenderDataPtr;
	typedef boost::shared_ptr<Texture>						TexturePtr;
	typedef boost::shared_ptr<GFX>							GFXPtr;


}
