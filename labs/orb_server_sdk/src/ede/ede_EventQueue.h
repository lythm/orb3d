#pragma once

#include "ede_event.h"

namespace orb
{
	namespace ede
	{
		class EventQueue
		{
		public:
			EventQueue();
			virtual ~EventQueue();

			void								Push(const EventPtr& e);

			EventPtr							Pop();
			
			void								Wait();

		private:
			std::queue<EventPtr>				m_queue;

		};
	}
}

