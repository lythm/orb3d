#pragma once

#include "core/EventDispatcher.h"

namespace engine
{

	class EventManager : public EventDispatcher
	{
	public:
		EventManager(void);
		virtual ~EventManager(void);

		void								DispatchEvents();

		void								PushEvent(EventPtr pEvent);
		void								PushEvent(EventDispatcherPtr pDispatcher, EventPtr pEvent);
		void								ClearEvents();


	private:

		std::vector<EventPtr>				m_queue;

	};

}