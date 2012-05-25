#include "framework_pch.h"
#include "..\..\include\framework\EngineMain.h"
#include "framework\GameEngine.h"

#include "GameManager.h"
#include "EngineConfig.h"

namespace engine
{
	EngineMain::EngineMain(void)
	{
		
	}


	EngineMain::~EngineMain(void)
	{
	}
	bool EngineMain::Initialize(const EngineParameters& param)
	{
		m_pEngineConfig = EngineConfigPtr(new EngineConfig);
		if(m_pEngineConfig->Load(param.config_file.c_str()) == false)
		{
			return false;
		}

		

		m_pGameEngine = GameEnginePtr(new GameEngine);

		CoreParameters core_param;

		core_param.input.module = m_pEngineConfig->Settings(L"sys_input", 0);
		core_param.input.app_handle = param.app_handle;

		core_param.graphics.app_handle = param.app_handle;
		core_param.graphics.module = m_pEngineConfig->Settings(L"sys_graphics", 0);
		core_param.graphics.width = 800;
		core_param.graphics.height = 600;
		if(m_pGameEngine->Initialize(core_param) == false)
		{
			return false;
		}

		m_pGameManager = GameManagerPtr(new GameManager);
		
		if(m_pGameManager->Initialize(m_pEngineConfig->Settings(L"game", 0)) == false)
		{
			return false;
		}

		GameInterface* pGame = m_pGameManager->GetGame();

		if(false == pGame->Initialize(m_pGameEngine))
		{
			return false;
		}

		return true;
	}
	void EngineMain::Release()
	{
		if(m_pGameManager)
		{
			m_pGameManager->GetGame()->Release();
			m_pGameManager->Release();
			m_pGameManager.reset();
		}

		if(m_pGameEngine)
		{
			m_pGameEngine->Release();
			m_pGameEngine.reset();
		}
	}
	bool EngineMain::Update()
	{

		// update core
		m_pGameEngine->GetEngineCore()->Update();

		// update modules



		// update game
		if(false == m_pGameManager->GetGame()->Update())
		{
			return false;
		}


		// render 

		// render modules
		SysGraphicsPtr pGraphics = m_pGameEngine->GetSysGraphics();
		
		pGraphics->SetRenderTarget(Texture2DPtr());
		pGraphics->ClearRenderTarget();

		pGraphics->Render();


		pGraphics->ClearRenderQueue();

		pGraphics->Present();

		return true;
	}

	GameEnginePtr EngineMain::GetEngine()
	{
		return m_pGameEngine;
	}
}
