#include "framework_pch.h"
#include "..\..\include\framework\GameEngine.h"

#include "GameManager.h"
#include "EngineConfig.h"

namespace engine
{
	GameEngine::GameEngine(void)
	{

	}


	GameEngine::~GameEngine(void)
	{
	}
	bool GameEngine::Initialize(const CoreParameters& param)
	{
		m_pEngineCore = EngineCorePtr(new EngineCore);

		if(m_pEngineCore->Initialize(param) == false)
		{
			return false;
		}
		return true;
	}
	void GameEngine::Release()
	{
		if(m_pEngineCore)
		{
			m_pEngineCore->Release();
			m_pEngineCore.reset();
		}

	}

	EngineCorePtr GameEngine::GetEngineCore()
	{
		return m_pEngineCore;
	}

	SysInputPtr GameEngine::GetSysInput()
	{
		return m_pEngineCore->GetSysInput();
	}
	SysGraphicsPtr GameEngine::GetSysGraphics()
	{
		return m_pEngineCore->GetSysGraphics();
	}

	void* GameEngine::MemAlloc(uint64 bytes)
	{
		return m_pEngineCore->MemAlloc(bytes);
	}
	void GameEngine::MemFree(void* pMem)
	{
		m_pEngineCore->MemFree(pMem);
	}
}
