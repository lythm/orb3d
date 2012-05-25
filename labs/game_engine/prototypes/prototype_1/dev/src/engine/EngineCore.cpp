#include "engine_pch.h"
#include "..\..\include\engine\EngineCore.h"

namespace engine
{
	EngineCore::EngineCore(void)
	{
	}


	EngineCore::~EngineCore(void)
	{
	}
	bool EngineCore::Init()
	{
		Event e;
		e.id = 0;

		DispatchEvent(e);

		return true;
	}

	void EngineCore::Update()
	{
	}

	void EngineCore::Release()
	{
	}
	bool EngineCore::DispatchEvent(Event& e)
	{
		return m_eventDispatcher.DispatchEvent(e.id, e);
	}
	
}