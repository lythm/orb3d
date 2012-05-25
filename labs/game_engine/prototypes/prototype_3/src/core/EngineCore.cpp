#include "core_pch.h"
#include "..\..\include\core\EngineCore.h"
#include "SysManager.h"
#include "input\SysInput.h"
#include "graphics\SysGraphics.h"

#include "MemManager.h"
#include "GameObjectManager.h"


namespace engine
{

	EngineCore::EngineCore(void)
	{
	}


	EngineCore::~EngineCore(void)
	{
	}
	bool EngineCore::Initialize(const CoreParameters& param)
	{
		m_pMemManager = MemManagerPtr(new MemManager);

		if(m_pMemManager == NULL || 
			m_pMemManager->Initialize() == false)
		{
			return false;
		}

		
		m_pSysManager = SysManagerPtr(new SysManager);
			
		
		m_pSysGraphics = m_pSysManager->LoadSysGraphics(param.graphics.module.c_str());
		if(m_pSysGraphics == NULL)
		{
			return false;
		}

		if(m_pSysGraphics == NULL ||
			m_pSysGraphics->Initialize(param.graphics) == false)
		{
			return false;
		}

		m_pSysInput = m_pSysManager->LoadSysInput(param.input.module.c_str());
		if(m_pSysInput == NULL || 
			m_pSysInput->Initialize(param.input) == false)
		{
			return false;
		}


		m_pGameObjectManager = GameObjectManagerPtr(new GameObjectManager);

		return true;
	}
	void EngineCore::Release()
	{

		m_pGameObjectManager->Release();


		m_pSysGraphics->Release();
		m_pSysGraphics.reset();
		
		m_pSysInput->Release();
		m_pSysInput.reset();

		m_pSysManager.reset();

		

		m_pMemManager->Release();
	}
	void EngineCore::Update()
	{
		update_fps();

		m_pSysInput->Update();
	}

	SysGraphicsPtr EngineCore::GetSysGraphics()
	{
		return m_pSysGraphics;
	}
	SysInputPtr EngineCore::GetSysInput()
	{
		return m_pSysInput;
	}
	void* EngineCore::MemAlloc(uint64 bytes)
	{
		return m_pMemManager->Alloc(bytes);
	}
	void EngineCore::MemFree(void* pMem)
	{
		m_pMemManager->Free(pMem);
	}
	void EngineCore::update_fps()
	{
		static int iframe = 0;
		static int tick = GetTickCount();

		int dt = GetTickCount() - tick;

		if(dt > 1000)
		{
			char szBuffer[1000];
			sprintf(szBuffer, "fps: %.4f\n", float(iframe) / float(dt) * 1000.0f);
			iframe = 0;
			tick = GetTickCount();

			OutputDebugStringA(szBuffer);
		}

		iframe++;
	}
}
