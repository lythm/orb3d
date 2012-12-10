#pragma once

namespace engine
{
	enum 
	{
		EV_WINMSG,
	};
	class Event
	{
	public:
		Event(void){}
		virtual ~Event(void){}

		uint32								id;
	};

#if defined(WIN32) || defined(WIN64)
	class WMEvent : public Event
	{
	public:
		WMEvent()
		{
			id = EV_WINMSG;
		}
		virtual ~WMEvent(){}

		MSG									msg;
	};
#endif
}
