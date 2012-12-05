#pragma once
#include "core\EventDispatcher.h"

namespace engine
{
	class EXPORT_CLASS CoreApi
	{
	public:
		CoreApi(void);
		virtual ~CoreApi(void);

		void											Update();
		bool											Initialize(const GraphicsSetting& graphicsSetting);
		void											Release();
		void											HandleMessage(MSG& msg);
		
		GameObjectManagerPtr							GetGameObjectManager();
		Sys_GraphicsPtr									GetSysGraphics();
		Sys_InputPtr									GetSysInput();

		void											Render();
		void											AddRenderData(RenderDataPtr pData);
		void											ClearRenderQueue();

		RenderSystemPtr									GetRenderSystem();

		GameObjectPtr									CreateGameObject(const std::wstring& name);
		GameObjectComponentPtr							CreateGameObjectComponent(const std::wstring& name);
		GameObjectPtr									GetRoot();

		void											DispatchEvent(EventPtr pEvent);
		void											AddEventHandler(uint32 id, EventDispatcher::EventHandler handler);
	private:
		
		
	private:
		GameObjectManagerPtr							m_pObjectManager;
		SysManagerPtr									m_pSysManager;
		Sys_GraphicsPtr									m_pSysGraphics;
		Sys_InputPtr									m_pSysInput;
		EventDispatcherPtr								m_pEventDispatcher;

		RenderSystemPtr									m_pRenderSystem;
	};
}
