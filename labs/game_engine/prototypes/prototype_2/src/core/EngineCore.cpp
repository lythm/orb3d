#include "core_pch.h"
#include "core\EngineCore.h"
#include "core\EventManager.h"
#include "core\Event.h"
#include "core\AssetsManager.h"

#include "SysManager.h"

#include "graphics\Sys_Graphics.h"
#include "core\SceneManager.h"
#include "core/UIManager.h"

#include "core/memmanager.h"

namespace engine
{
	EngineCore::EngineCore(void)
	{
	}


	EngineCore::~EngineCore(void)
	{
	}
	bool EngineCore::Initialize(const EngineParameters& param)
	{
		m_pMemManager = MemManagerPtr(new MemManager);

		if(m_pMemManager->Initialize() == false)
		{
			return false;
		}

		m_pSysManager = SysManagerPtr(new SysManager);


		m_pAssetsManager = AssetsManagerPtr(new AssetsManager);


		m_pInput = m_pSysManager->LoadSysInput(param.input.inputMod.c_str());

		if(false == m_pInput->Initialize(param.input))
		{
			return false;
		}

		m_pGraphics =  m_pSysManager->LoadSysGraphics(param.graphics.graphicsMod.c_str());

		if(m_pGraphics == NULL)
		{
			return false;
		}

			
		if(false == m_pGraphics->Initialize(param.graphics))
		{
			return false;
		}
		
		m_pGraphics->SetClearColor(math::Color4(0.2f, 0.5f, 0.5f, 1.0f));
		m_pEventManager = EventManagerPtr(new EventManager);

		m_pEventManager->AddEventHandler(0, boost::bind(&EngineCore::on_update, this, _1));


		m_pSceneManager = SceneManagerPtr(new SceneManager);


		if(m_pSceneManager->Initialize(m_pGraphics) == false)
		{
			return false;
		}


		m_pUIManager = UIManagerPtr(new UIManager);

		return true;
	}
	void EngineCore::Release()
	{

		m_pSceneManager->Release();
		m_pSceneManager.reset();


		m_pGraphics->Release();
		m_pGraphics.reset();

		m_pInput->Release();
		m_pInput.reset();
	
		m_pMemManager->Release();
		m_pMemManager.reset();
	}
	void EngineCore::update_fps()
	{
		static int iframe = 0;
		static int tick = GetTickCount();

		int dt = GetTickCount() - tick;

		if(dt > 1000)
		{
			char szBuffer[1000];
			sprintf(szBuffer, "fps: %.4f", float(iframe) / float(dt) * 1000.0f);
			iframe = 0;
			tick = GetTickCount();

			debug::Trace(szBuffer);
		}

		iframe++;
	}


	void EngineCore::Update()
	{
		update_fps();
		

		EventPtr pEvent = m_pMemManager->AllocObject<Event>();
		//EventPtr pEvent = EventPtr(new Event);

		pEvent->id = 0;

		m_pEventManager->PushEvent(pEvent);


		m_pEventManager->DispatchEvents();

		m_pSceneManager->Update();

		m_pUIManager->Update();


		m_pGraphics->ClearRenderTarget();

		m_pSceneManager->Render();

		m_pUIManager->Render();

		m_pGraphics->Present();
	}
	
	void EngineCore::AddEventHandler(uint32 id, const EventDispatcher::EventHandler& handler)
	{
		m_pEventManager->AddEventHandler(id, handler);
	}
	void EngineCore::PushEvent(EventPtr pEvent)
	{
		m_pEventManager->PushEvent(pEvent);
	}

	void EngineCore::PushEvent(EventDispatcherPtr pTarget, EventPtr pEvent)
	{
		m_pEventManager->PushEvent(pTarget, pEvent);
	}
	void EngineCore::on_update(EventPtr pEvent)
	{
		

	//	debug::Trace("on update");
	}
}
