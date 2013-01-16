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
		typedef boost::function<void (const std::wstring& log)>			Log;

		CoreApi(void);
		virtual ~CoreApi(void);

		void											Update();
		bool											Initialize(const GraphicsSetting& graphicsSetting, Allocator* pAlloc = nullptr);
		void											Release();
		void											HandleMessage(MSG& msg);
		
		GameObjectManagerPtr							GetGameObjectManager();
		Sys_GraphicsPtr									GetSysGraphics();
		Sys_InputPtr									GetSysInput();

		void											Render();
		void											Render(BaseCameraPtr pCamera);
		void											Present();
		void											AddRenderData(RenderDataPtr pData);
		void											ClearRenderQueue();

		RenderSystemPtr									GetRenderSystem();

		GameObjectPtr									CreateGameObject(const std::wstring& name);
		GameObjectComponentPtr							CreateGameObjectComponent(const std::wstring& name);
		GameObjectPtr									CreatGameObjectFromTemplate(const std::wstring& tpl, const std::wstring& name);
		GameObjectPtr									Root();

		void											DispatchEvent(EventPtr pEvent);
		void											AddEventHandler(uint32 id, EventDispatcher::EventHandler handler);

		ScenePtr										GetScene();
		void											ResetScene();
		static Allocator*								GetAllocator();
	private:
		GameObjectManagerPtr							m_pObjectManager;
		SysManagerPtr									m_pSysManager;
		Sys_GraphicsPtr									m_pSysGraphics;
		Sys_InputPtr									m_pSysInput;
		Sys_SoundPtr									m_pSysSound;
		EventDispatcherPtr								m_pEventDispatcher;

		RenderSystemPtr									m_pRenderSystem;

		static Allocator*								s_pAllocator;

		ScenePtr										m_pScene;
	};
}
