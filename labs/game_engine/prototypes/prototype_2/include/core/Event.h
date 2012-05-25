#pragma once

namespace engine
{
	class EventDispatcher;

	class Event
	{
	public:

		Event(void){}

		virtual ~Event(void){}


		
		EventDispatcherPtr				pTarget;

		uint32							id;

		std::string						name;
	};
	
}
