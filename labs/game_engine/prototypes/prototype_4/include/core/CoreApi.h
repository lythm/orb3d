#pragma once
#include "core\EventDispatcher.h"

namespace engine
{
	class EXPORT_CLASS CoreApi 
	{
	public:
		typedef boost::shared_ptr<MemPool>				MemPoolPtr;
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
		void											Present();
		void											AddRenderData(RenderDataPtr pData);
		void											ClearRenderQueue();

		RenderSystemPtr									GetRenderSystem();

		GameObjectPtr									CreateGameObject(const std::wstring& name);
		GameObjectComponentPtr							CreateGameObjectComponent(const std::wstring& name);
		GameObjectPtr									GetRoot();

		void											DispatchEvent(EventPtr pEvent);
		void											AddEventHandler(uint32 id, EventDispatcher::EventHandler handler);


		static void*									MemAlloc(uint64 bytes);
		static void										MemFree(void* mem);


		template<typename T>
		static
		boost::shared_ptr<T>							AllocObject()
		{
			return s_pMemPool->AllocObject<T>();
		}

		template<typename T, typename TP>
		static
		boost::shared_ptr<T>							AllocObject(TP param)
		{
			return s_pMemPool->AllocObject<T, TP>(param);
		}

		static MemPoolPtr								GetMemPool();

	private:
		
		
	private:
		GameObjectManagerPtr							m_pObjectManager;
		SysManagerPtr									m_pSysManager;
		Sys_GraphicsPtr									m_pSysGraphics;
		Sys_InputPtr									m_pSysInput;
		EventDispatcherPtr								m_pEventDispatcher;

		RenderSystemPtr									m_pRenderSystem;

		static MemPoolPtr								s_pMemPool;						
	};
}
