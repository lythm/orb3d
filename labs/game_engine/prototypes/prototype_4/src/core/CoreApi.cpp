#include "core_pch.h"
#include "..\..\include\core\CoreApi.h"

#include "core\SysManager.h"
#include "core\Sys_Graphics.h"
#include "core\GameObjectManager.h"
#include "core\RenderSystem.h"


#include "core\Event.h"
#include "core\PoolAllocator.h"
#include "core\StdAllocator.h"
#include "core\Scene.h"

#include "core\GameObject.h"

#include "WMInput.h"


namespace engine
{
	Allocator*										CoreApi::s_pAllocator;

	static StdAllocator								g_stdAllocator;

	CoreApi::CoreApi(void)
	{
	}


	CoreApi::~CoreApi(void)
	{
	}
	void CoreApi::Update()
	{
		m_pScene->Update();
	}
	bool CoreApi::Initialize(const GraphicsSetting& graphicsSetting, Allocator* pAlloc)
	{
		s_pAllocator = pAlloc;

		if(s_pAllocator == nullptr)
		{
			s_pAllocator = &g_stdAllocator;
		}
		
		m_pEventDispatcher = s_pAllocator->AllocObject<EventDispatcher>();


		m_pSysManager = s_pAllocator->AllocObject<SysManager>();

		m_pSysGraphics = m_pSysManager->LoadSysGraphics(graphicsSetting.sysMod.c_str());

		if(m_pSysGraphics == Sys_GraphicsPtr())
		{
			return false;
		}
		if(false == m_pSysGraphics->Initialize(graphicsSetting))
		{
			return false;
		}

		m_pSysInput = s_pAllocator->AllocObject<WMInput>();

		if(false == m_pSysInput->Initialize(graphicsSetting.wnd))
		{
			return false;
		}

		m_pRenderSystem = s_pAllocator->AllocObject<RenderSystem>();
		if(m_pRenderSystem->Initialize(m_pSysGraphics) == false)
		{
			return false;
		}
		m_pObjectManager = s_pAllocator->AllocObject<GameObjectManager>();
		if(m_pObjectManager->Initialize(shared_from_this()) == false)
		{
			return false;
		}

		m_pScene = s_pAllocator->AllocObject<Scene, GameObjectManagerPtr>(m_pObjectManager);

		return true;
	}
	void CoreApi::Release()
	{
		if(m_pScene)
		{
			m_pScene->Release();
			m_pScene.reset();
		}
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

		s_pAllocator	= nullptr;
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
		boost::shared_ptr<WMEvent> pEvent = s_pAllocator->AllocObject<WMEvent, MSG>(msg);
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
		GameObjectPtr pObj = m_pObjectManager->CreateGameObject(name);
		pObj->LinkTo(m_pScene->Root());

		return pObj;
	}
	GameObjectPtr CoreApi::CreatGameObjectFromTemplate(const std::wstring& tpl, const std::wstring& name)
	{
		GameObjectPtr pObj = m_pObjectManager->CreateObjectFromTemplate(tpl);

		if(pObj == nullptr)
		{
			return GameObjectPtr();
		}
		if(name != L"")
		{
			pObj->SetName(name);
		}

		pObj->LinkTo(m_pScene->Root());
		return pObj;

	}
	GameObjectPtr CoreApi::Root()
	{
		return m_pScene->Root();
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
		
	void CoreApi::Present()
	{
		if(m_pRenderSystem)
		{
			m_pRenderSystem->Present();
		}
	}
	Allocator* CoreApi::GetAllocator()
	{
		return s_pAllocator;
	}
	ScenePtr CoreApi::GetScene()
	{
		return m_pScene;
	}
	void CoreApi::ResetScene()
	{
		m_pScene->Reset();
	}
}
