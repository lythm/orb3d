#pragma once

namespace engine
{
	class EventDispatcher
	{
	public:

		typedef boost::function<void (EventPtr)>		EventHandler;

		typedef std::vector<EventHandler>				HandlerArray;

		typedef boost::unordered_map<uint32, HandlerArray> HandlerMap;




		EventDispatcher(void);
		virtual ~EventDispatcher(void);


		void									DispatchEvent(EventPtr pEvent);
		void									AddEventHandler(uint32 id, const EventHandler& handler);
	private:


	private:
		HandlerMap								m_HandlerMap;

	};


}