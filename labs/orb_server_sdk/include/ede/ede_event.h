#pragma once

namespace orb
{
	namespace ede
	{
		typedef uint64							EventId;
		typedef uint64							EDObjectId;
		struct Event
		{
			EventId								id;
			EDObjectId							source;
		};

		template <typename T>
		class EventPtr_T
		{
		public:
			EventPtr_T(T*)
			{
			}

		};

		typedef EventPtr_T<Event>				EventPtr;
	}
}
