#include "core_pch.h"
#include "..\..\include\core\CoreApi.h"

#include "core\SysManager.h"
#include "core\Sys_Graphics.h"
#include "core\GameObjectManager.h"
#include "core\RenderSystem.h"


#include "core\meshdata.h"
#include "core\meshrenderer.h"
#include "core\Event.h"
#include "core\PoolAllocator.h"
#include "core\StdAllocator.h"



#include "WMInput.h"


namespace engine
{
	AllocatorPtr									CoreApi::s_pAllocator;

	CoreApi::CoreApi(void)
	{
	}


	CoreApi::~CoreApi(void)
	{
	}
	void CoreApi::Update()
	{
		m_pObjectManager->UpdateObjects();
	}
	bool CoreApi::Initialize(const GraphicsSetting& graphicsSetting)
	{
		if(s_pAllocator == nullptr)
		{
			PoolAllocator* pAlloc = new PoolAllocator;
			if(pAlloc->Initialize() == false)
			{
				delete pAlloc;
				return false;
			}

			s_pAllocator = AllocatorPtr(pAlloc);
		}

		m_pEventDispatcher = AllocObject<EventDispatcher>();


		m_pSysManager = AllocObject<SysManager>();

		m_pSysGraphics = m_pSysManager->LoadSysGraphics(graphicsSetting.sysMod.c_str());

		if(m_pSysGraphics == Sys_GraphicsPtr())
		{
			return false;
		}
		if(false == m_pSysGraphics->Initialize(graphicsSetting))
		{
			return false;
		}

		m_pSysInput = AllocObject<WMInput>();

		if(false == m_pSysInput->Initialize(graphicsSetting.wnd))
		{
			return false;
		}

		m_pRenderSystem = AllocObject<RenderSystem>();
		if(m_pRenderSystem->Initialize(m_pSysGraphics) == false)
		{
			return false;
		}
		m_pObjectManager = AllocObject<GameObjectManager>();
		if(m_pObjectManager->Initialize() == false)
		{
			return false;
		}
		return true;
	}
	void CoreApi::Release()
	{
		if(m_pObjectManager)
		{
			m_pObjectManager->Release();
			m_pObjectManager.reset();
		}

		if(m_pRenderSystem)
		{
			m_pRenderSystem->Release();
			m_pRenderSystem.reset();
		}

		if(m_pSysInput)
		{
			m_pSysInput->Release();
			m_pSysInput.reset();
		}
		if(m_pSysGraphics)
		{
			m_pSysGraphics->Release();
			m_pSysGraphics.reset();
		}

		m_pSysManager.reset();

		if(m_pEventDispatcher)
		{
			m_pEventDispatcher->Clear();
			m_pEventDispatcher.reset();
		}

		if(s_pAllocator)
		{
			s_pAllocator->Release();
			s_pAllocator.reset();
		}
	}


	GameObjectManagerPtr CoreApi::GetGameObjectManager()
	{
		return m_pObjectManager;
	}
	Sys_GraphicsPtr	CoreApi::GetSysGraphics()
	{
		return m_pSysGraphics;
	}
	Sys_InputPtr CoreApi::GetSysInput()
	{
		return m_pSysInput;
	}
	void CoreApi::HandleMessage(MSG& msg)
	{
		boost::shared_ptr<WMEvent> pEvent = AllocObject<WMEvent, MSG>(msg);
		pEvent->msg = msg;

		DispatchEvent(pEvent);

		if(m_pSysInput)
		{
			m_pSysInput->HandleMessage(msg);
		}
	}
	void CoreApi::Render()
	{
		if(m_pRenderSystem)
		{
			m_pRenderSystem->Render();
		}
	}
	void CoreApi::AddRenderData(RenderDataPtr pData)
	{
		if(m_pRenderSystem)
		{
			m_pRenderSystem->AddRenderData(pData);
		}
	}
	void CoreApi::ClearRenderQueue()
	{
		if(m_pRenderSystem)
		{
			m_pRenderSystem->Clear();
		}
	}
	RenderSystemPtr	CoreApi::GetRenderSystem()
	{
		return m_pRenderSystem;
	}
	GameObjectPtr CoreApi::CreateGameObject(const std::wstring& name)
	{
		return m_pObjectManager->CreateGameObject(name);
	}
	GameObjectPtr CoreApi::GetRoot()
	{
		return m_pObjectManager->GetRoot();
	}
	GameObjectComponentPtr CoreApi::CreateGameObjectComponent(const std::wstring& name)
	{
		return m_pObjectManager->CreateComponent(name);
	}
	void CoreApi::DispatchEvent(EventPtr pEvent)
	{
		m_pEventDispatcher->DispatchEvent(pEvent);
	}
	void CoreApi::AddEventHandler(uint32 id, EventDispatcher::EventHandler handler)
	{
		m_pEventDispatcher->AddEventHandler(id, handler);
	}
	void* CoreApi::MemAlloc(uint64 bytes)
	{
		return s_pAllocator->Alloc(bytes);
	}
	void CoreApi::MemFree(void* mem)
	{
		s_pAllocator->Free(mem);
	}
	
	void CoreApi::Present()
	{
		if(m_pRenderSystem)
		{
			m_pRenderSystem->Present();
		}
	}
}
