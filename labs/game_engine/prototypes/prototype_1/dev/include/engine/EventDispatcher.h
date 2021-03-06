#pragma once

#include "lang\types.h"

#include <boost\function.hpp>
#include <boost\unordered_map.hpp>
#include <list>
#include <boost\signal.hpp>

namespace engine
{
	template<typename Event_T>
	class EventDispatcher
	{
	public:

		typedef boost::function<void (uint32, Event_T&)>								EventHandler;
		typedef std::list<EventHandler>													EventHandlerList;	
		typedef boost::unordered_map<uint32,  EventHandlerList>							EventHandlerMap;
		typedef boost::signal<void (uint32, Event_T&)>									EventSignal;


		EventDispatcher(void){}
		virtual ~EventDispatcher(void){}


		bool DispatchEvent(uint32 id, Event_T& e)
		{
			
			handler_EventFilter(id,e);
			
			typename EventHandlerMap::iterator it = m_handlers.find(id);
			
			if(it == m_handlers.end())
			{
				handler_UnhandledEvent(id, e);
				return false;
			}

			if(it->second.size() == 0)
			{
				handler_UnhandledEvent(id, e);
				return false;
			}

			typename EventHandlerList::iterator list_it = it->second.begin();

			for(; list_it != it->second.end(); ++list_it)
			{
				(*list_it)(id, e);
			}

			return true;
		}

		void AddEventHandler(uint32 id, const EventHandler& handler)
		{
			m_handlers[id].push_back(handler);
		}


		void AddUnhandledEventHandler(const EventHandler& handler)
		{
			handler_UnhandledEvent.connect(handler);
		}

		void AddEventFilter(const EventHandler& handler)
		{
			handler_EventFilter.connect(handler);
		}

		void Clear()
		{
			if(!handler_EventFilter.empty())
			{
				handler_EventFilter.disconnect_all_slots();
			}

			m_handlers.clear();

			if(!handler_UnhandledEvent.empty())
			{
				handler_UnhandledEvent.disconnect_all_slots();
			}
		}
	private:
		
	private:

		EventSignal												handler_EventFilter;

		EventHandlerMap											m_handlers;

		EventSignal												handler_UnhandledEvent;

	};

}
