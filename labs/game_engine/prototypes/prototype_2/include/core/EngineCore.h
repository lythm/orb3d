#pragma once

#include <core/EngineParameters.h>
#include <core/EventManager.h>


namespace engine
{
	class EXPORT_CLASS EngineCore
	{
	public:
		EngineCore(void);
		virtual ~EngineCore(void);

		bool								Initialize(const EngineParameters& param);

		void								Release();
		
		void								Update();

		void								AddEventHandler(uint32 id, const EventDispatcher::EventHandler& handler);
		void								PushEvent(EventPtr pEvent);
		void								PushEvent(EventDispatcherPtr pTarget, EventPtr pEvent);

	private:
		
		void								on_update(EventPtr pEvent);
		void								update_fps();
	private:
		Sys_GraphicsPtr						m_pGraphics;

		Sys_InputPtr						m_pInput;
		
		EventManagerPtr						m_pEventManager;

		AssetsManagerPtr					m_pAssetsManager;

		SysManagerPtr						m_pSysManager;

		SceneManagerPtr						m_pSceneManager;

		UIManagerPtr						m_pUIManager;

		MemManagerPtr						m_pMemManager;
	};

}
