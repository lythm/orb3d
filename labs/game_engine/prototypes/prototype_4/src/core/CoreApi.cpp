#include "core_pch.h"
#include "..\..\include\core\CoreApi.h"

#include "core\SysManager.h"
#include "core\Sys_Graphics.h"
#include "core\GameObjectManager.h"
#include "core\RenderSystem.h"


#include "core\meshdata.h"
#include "core\meshrenderer.h"
#include "core\Event.h"



#include "WMInput.h"


namespace engine
{

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
		m_pEventDispatcher = EventDispatcherPtr(new EventDispatcher);

		m_pSysManager = SysManagerPtr(new SysManager);
		
		m_pSysGraphics = m_pSysManager->LoadSysGraphics(L"./d11graphics.dll");

		if(m_pSysGraphics == Sys_GraphicsPtr())
		{
			return false;
		}
		if(false == m_pSysGraphics->Initialize(graphicsSetting))
		{
			return false;
		}

		m_pSysInput = boost::shared_ptr<WMInput>(new WMInput);

		if(false == m_pSysInput->Initialize(graphicsSetting.wnd))
		{
			return false;
		}

		m_pRenderSystem = RenderSystemPtr(new RenderSystem);
		if(m_pRenderSystem->Initialize(m_pSysGraphics) == false)
		{
			return false;
		}
		m_pObjectManager = GameObjectManagerPtr(new engine::GameObjectManager);
		if(m_pObjectManager->Initialize() == false)
		{
			return false;
		}
		return true;
	}
	void CoreApi::Release()
	{
		m_pObjectManager->Release();
		m_pObjectManager.reset();
		
		m_pRenderSystem->Release();
		m_pRenderSystem.reset();

		m_pSysInput->Release();
		m_pSysInput.reset();

		m_pSysGraphics->Release();
		m_pSysGraphics.reset();

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
		EventPtr pEvent = EventPtr(new WMEvent(msg));

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
}
