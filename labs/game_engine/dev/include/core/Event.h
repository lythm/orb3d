#pragma once

namespace ld3d
{
	enum EVENT_ID
	{
		EV_WINMSG,
		EV_RESIZE_FRAMEBUFFER,
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

	class Event_ResizeFrameBuffer : public Event
	{
	public:
		Event_ResizeFrameBuffer(int cx, int cy) : Event(EV_RESIZE_FRAMEBUFFER)
		{
			m_width = cx;
			m_height = cy;
		}

		int							m_width;
		int							m_height;
	};
#if defined(WIN32) || defined(WIN64)
	class Event_WindowMessage: public Event
	{
	public:
		Event_WindowMessage(const MSG& m) : Event(EV_WINMSG)
		{
			msg = m;
		}
		virtual ~Event_WindowMessage(){}

		MSG									msg;
	};
#endif
}
