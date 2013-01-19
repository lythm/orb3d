#pragma once

#include <boost\shared_ptr.hpp>

#include "core\ext\core_ext_ptr.h"

namespace ld3d
{
	class GameObject;
	class GameObjectManager;
	class GameObjectComponent;
	class Scene;

	typedef boost::shared_ptr<Scene>											ScenePtr;
	typedef boost::shared_ptr<GameObjectManager>								GameObjectManagerPtr;
	typedef boost::shared_ptr<GameObject>										GameObjectPtr;
	typedef boost::shared_ptr<GameObjectComponent>								GameObjectComponentPtr;


	

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

	class LightManager;
	class Light;
	class PointLight;
	class DirectionalLight;
	class SpotLight;
	class SkyLight;

	typedef boost::shared_ptr<LightManager>					LightManagerPtr;
	typedef boost::shared_ptr<Light>						LightPtr;
	typedef boost::shared_ptr<PointLight>					PointLightPtr;
	typedef boost::shared_ptr<DirectionalLight>				DirectionalLightPtr;
	typedef boost::shared_ptr<SpotLight>					SpotLightPtr;
	typedef boost::shared_ptr<SkyLight>						SkyLightPtr;
	
	class DataStream;
	class Mesh;
	class SubMesh;
	


	typedef boost::shared_ptr<SubMesh>						SubMeshPtr;
	typedef boost::shared_ptr<DataStream>					DataStreamPtr;
	typedef boost::shared_ptr<Mesh>							MeshPtr;

	class DepthStencilBuffer;
	class RenderData;
	class RenderTarget;
	class Texture;
	class Material;
	class GPUBuffer;
	class Camera;
	class RenderState;
	class Shader;
	class BaseCamera;

	typedef boost::shared_ptr<RenderState>					RenderStatePtr;
	typedef boost::shared_ptr<Shader>						ShaderPtr;
	typedef boost::shared_ptr<Camera>						CameraPtr;
	typedef boost::shared_ptr<BaseCamera>					BaseCameraPtr;
	typedef boost::shared_ptr<DepthStencilBuffer>			DepthStencilBufferPtr;
	typedef boost::shared_ptr<RenderTarget>					RenderTargetPtr;
	typedef boost::shared_ptr<RenderData>					RenderDataPtr;
	typedef boost::shared_ptr<GPUBuffer>					GPUBufferPtr;
	typedef boost::shared_ptr<Texture>						TexturePtr;
	typedef boost::shared_ptr<Material>						MaterialPtr;


	class CoreApi;
	class RenderSystem;
	class PostEffectManager;
	class PostEffect;
	class PostEffect_SSAO;
	class PostEffect_GaussianBlur;

	typedef boost::shared_ptr<PostEffect_GaussianBlur>		PostEffect_GaussianBlurPtr;
	typedef boost::shared_ptr<PostEffect_SSAO>				PostEffect_SSAOPtr;
	typedef boost::shared_ptr<PostEffect>					PostEffectPtr;
	typedef boost::shared_ptr<PostEffectManager>			PostEffectManagerPtr;
	typedef boost::shared_ptr<RenderSystem>					RenderSystemPtr;
	typedef boost::shared_ptr<CoreApi>						CoreApiPtr;


	class EventDispatcher;
	class Event;

	typedef boost::shared_ptr<Event>						EventPtr;
	typedef boost::shared_ptr<EventDispatcher>				EventDispatcherPtr;


	class Sound;
	class SoundChannel;
	typedef boost::shared_ptr<Sound>						SoundPtr;
	typedef boost::shared_ptr<SoundChannel>					SoundChannelPtr;



	class PropertySet;
	class Property;

	typedef boost::shared_ptr<PropertySet>					PropertySetPtr;
	typedef boost::shared_ptr<Property>						PropertyPtr;

	

}
