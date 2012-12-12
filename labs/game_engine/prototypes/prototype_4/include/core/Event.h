#pragma once

namespace engine
{
	enum EVENT_ID
	{
		EV_WINMSG,
	};
	class Event
	{
	public:
		Event(uint32 _id)
		{
			id = _id;
		}
		virtual ~Event(void){}

		uint32								id;
	};

#if defined(WIN32) || defined(WIN64)
	class WMEvent : public Event
	{
	public:
		WMEvent(const MSG& m) : Event(EV_WINMSG)
		{
			msg = m;
		}
		virtual ~WMEvent(){}

		MSG									msg;
	};
#endif
}
