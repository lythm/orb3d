#pragma once

#include "engine\EventDispatcher.h"

#include "engine\Event.h"


namespace engine
{
	class EXPORT_CLASS EngineCore
	{
	public:
		EngineCore(void);
		virtual ~EngineCore(void);

		bool							Init();

		void							Update();

		void							Release();


		bool							DispatchEvent(Event& e);

	private:

	private:


		EventDispatcher<Event>			m_eventDispatcher;

	};


}