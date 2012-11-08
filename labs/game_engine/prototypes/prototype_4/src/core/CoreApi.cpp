#include "core_pch.h"
#include "..\..\include\core\CoreApi.h"

#include "core\SysManager.h"
#include "core\Sys_Graphics.h"
#include "core\GameObjectManager.h"
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
	bool CoreApi::Initialize(void* app_handle, int w, int h, G_FORMAT format)
	{

		m_pSysManager = SysManagerPtr(new SysManager);
		
		m_pSysGraphics = m_pSysManager->LoadSysGraphics(L"./d11graphics.dll");

		if(m_pSysGraphics == Sys_GraphicsPtr())
		{
			return false;
		}
		if(false == m_pSysGraphics->Initialize(app_handle, w, h, format))
		{
			return false;
		}

		m_pSysGraphics->SetClearColor(math::Color4(0.2f, 0.2f, 0.2f, 1.0f));
		
		m_pSysInput = boost::shared_ptr<WMInput>(new WMInput);

		if(false == m_pSysInput->Initialize(app_handle))
		{
			return false;
		}
		m_pObjectManager = GameObjectManagerPtr(new engine::GameObjectManager);

		return true;
	}
	void CoreApi::Release()
	{
		m_pObjectManager->ReleaseAllObject();
		m_pObjectManager.reset();
		

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
		if(m_pSysInput)
		{
			m_pSysInput->HandleMessage(msg);
		}
	}
}
