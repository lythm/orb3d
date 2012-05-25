#include "core_pch.h"
#include "core\EventManager.h"
#include "core/Event.h"

namespace engine
{
	EventManager::EventManager(void)
	{
	}


	EventManager::~EventManager(void)
	{
	}

	void EventManager::DispatchEvents()
	{
		for(size_t i = 0; i < m_queue.size(); ++i)
		{
			EventPtr pEvent = m_queue[i];

			if(pEvent->pTarget == NULL)
			{
				this->DispatchEvent(pEvent);
			}
			else
			{
				pEvent->pTarget->DispatchEvent(pEvent);
			}
		}

		ClearEvents();

	}
	void EventManager::PushEvent(EventDispatcherPtr pDispatcher, EventPtr pEvent)
	{
		m_queue.push_back(pEvent);
	}
	void EventManager::PushEvent(EventPtr pEvent)
	{
		m_queue.push_back(pEvent);
	}
	void EventManager::ClearEvents()
	{
		m_queue.clear();
	}
}
