#include "ede_pch.h"
#include "ede_EventQueue.h"

namespace orb
{
	namespace ede
	{
		EventQueue::EventQueue()
		{
		}
		EventQueue::~EventQueue()
		{
		}

		void EventQueue::Push(const EventPtr& e)
		{
			m_queue.push(e);
		}

		EventPtr EventQueue::Pop()
		{

			if(m_queue.size() != 0)
			{
				EventPtr& e = m_queue.front();
				m_queue.pop();
				return e;
			}

			return EventPtr(NULL);
			
		}
		void EventQueue::Wait()
		{

		}
	}
}
