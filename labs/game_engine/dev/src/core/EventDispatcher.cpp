#include "core_pch.h"
#include "..\..\include\core\EventDispatcher.h"
#include "core\Event.h"

namespace ld3d
{
	EventDispatcher::EventDispatcher(void)
	{
	}


	EventDispatcher::~EventDispatcher(void)
	{
	}
	
	void EventDispatcher::DispatchEvent(EventPtr pEvent)
	{
		EventHandlers& handlers = m_HandlerMap[pEvent->id];

		handlers(pEvent);
		

	}
	EventDispatcher::EventHandlerHandle EventDispatcher::AddEventHandler(uint32 id, const EventHandler& handler)
	{
		EventHandlers& handlers = m_HandlerMap[id];

		return handlers.connect(handler);
	}
	void EventDispatcher::Clear()
	{
		m_HandlerMap.clear();
	}
	void EventDispatcher::RemoveEventHandler(EventHandlerHandle handler)
	{
		handler.disconnect();
	}
}
