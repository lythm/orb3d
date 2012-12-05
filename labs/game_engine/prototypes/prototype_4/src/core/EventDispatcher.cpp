#include "core_pch.h"
#include "..\..\include\core\EventDispatcher.h"
#include "core\Event.h"

namespace engine
{
	EventDispatcher::EventDispatcher(void)
	{
	}


	EventDispatcher::~EventDispatcher(void)
	{
	}
	
	void EventDispatcher::DispatchEvent(EventPtr pEvent)
	{
		HandlerArray& handlers = m_HandlerMap[pEvent->id];

		for(size_t i = 0;i < handlers.size(); ++i)
		{
			handlers[i](pEvent);
		}

	}
	void EventDispatcher::AddEventHandler(uint32 id, const EventHandler& handler)
	{
		HandlerArray& handlers = m_HandlerMap[id];

		handlers.push_back(handler);
	}
}