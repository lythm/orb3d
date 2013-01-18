#pragma once

#include <boost\signal.hpp>

namespace ld3d
{
	class EventDispatcher
	{
	public:

		typedef boost::function<void (EventPtr)>		EventHandler;

		typedef boost::signal<void (EventPtr)>			EventHandlers;

		typedef boost::signals::connection				EventHandlerHandle;

		typedef boost::unordered_map<uint32, EventHandlers> HandlerMap;




		EventDispatcher(void);
		virtual ~EventDispatcher(void);


		void									DispatchEvent(EventPtr pEvent);
		EventHandlerHandle						AddEventHandler(uint32 id, const EventHandler& handler);
		void									RemoveEventHandler(EventHandlerHandle handler);
		void									Clear();
	private:


	private:
		HandlerMap								m_HandlerMap;

	};


}