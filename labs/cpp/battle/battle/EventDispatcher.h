#pragma once


template<typename TEvent>
class EventDispatcher
{
public:

	typedef boost::function<void (int, const TEvent& e)>						EventHandler;
	typedef std::list<EventHandler>												EventHandlerList;	
	typedef boost::unordered_map<int,  EventHandlerList>						EventHandlerMap;


	EventDispatcher(void){}
	virtual ~EventDispatcher(void){}


	void DispatchEvent(int id, const TEvent& e)
	{
		EventHandlerMap::iterator it = m_handlers.find(id);
		if(it == m_handlers.end())
		{
			OnUnhandledEvent(id, e);
			return;
		}

		if(it->second.size() == 0)
		{
			OnUnhandledEvent(id, e);
			return;
		}

		for(EventHandlerList::iterator list_it = it->second.begin(); list_it != it->second.end(); ++list_it)
		{
			(*list_it)(id, e);
		}
	}

	void AddEventHandler(int id, const EventHandler& handler)
	{
		m_handlers[id].push_back(handler);
	}

	void AddUnhandledEventHandler(const EventHandler& handler)
	{
		handler_UnhandledEvent.push_back(handler);
	}

	void Clear()
	{
		m_handlers.clear();
	}
private:
	void OnUnhandledEvent(int id, const TEvent& e)
	{
		for(EventHandlerList::iterator list_it = handler_UnhandledEvent.begin(); list_it != handler_UnhandledEvent.end(); ++list_it)
		{
			(*list_it)(id, e);

		}

	}
private:

	EventHandlerMap											m_handlers;

	EventHandlerList										handler_UnhandledEvent;

};

