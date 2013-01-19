#pragma once
#include "core\EventDispatcher.h"
#include "core\Allocator.h"
#include "core\StdAllocator.h"

#include <boost\enable_shared_from_this.hpp>
namespace ld3d
{
	class EXPORT_CLASS CoreApi : public boost::enable_shared_from_this<CoreApi>
	{
	public:
		typedef boost::function<void (const std::wstring& log)>			Logger;

		CoreApi(void);
		virtual ~CoreApi(void);


		bool											Initialize(const SysSetting& setting, Allocator* pAlloc = nullptr);

		void											Update();
		
		void											Release();
		void											HandleMessage(MSG& msg);
		
		GameObjectManagerPtr							GetGameObjectManager();
		Sys_GraphicsPtr									GetSysGraphics();
		Sys_InputPtr									GetSysInput();
		Sys_SoundPtr									GetSysSound();

		void											Render();
		void											Render(CameraPtr pCamera);
		void											Present();
		void											AddRenderData(RenderDataPtr pData);
		void											ClearRenderQueue();
		
		void											AddCamera(CameraPtr pCamera);
		void											RemoveCamera(CameraPtr pCamera);

		RenderSystemPtr									GetRenderSystem();

		bool											LoadPackage(const std::wstring& packageFile);
		GameObjectPtr									CreateGameObject(const std::wstring& name);
		GameObjectComponentPtr							CreateGameObjectComponent(const std::wstring& name);
		GameObjectPtr									CreatGameObjectFromTemplate(const std::wstring& tpl, const std::wstring& name);
		GameObjectPtr									Root();

		void											DispatchEvent(EventPtr pEvent);
		EventDispatcher::EventHandlerHandle				AddEventHandler(uint32 id, EventDispatcher::EventHandler handler);
		void											RemoveEventHandler(EventDispatcher::EventHandlerHandle handle);
		ScenePtr										GetScene();
		void											ResetScene();
		static Allocator*								GetAllocator();

		static void										Log(const std::wstring& text);
		static void										SetLogger(Logger logger);
	private:
		GameObjectManagerPtr							m_pObjectManager;
		SysManagerPtr									m_pSysManager;
		Sys_GraphicsPtr									m_pSysGraphics;
		Sys_InputPtr									m_pSysInput;
		Sys_SoundPtr									m_pSysSound;
		EventDispatcherPtr								m_pEventDispatcher;

		RenderSystemPtr									m_pRenderSystem;

		static Allocator*								s_pAllocator;
		static Logger									s_logger;
		ScenePtr										m_pScene;
	};
}
