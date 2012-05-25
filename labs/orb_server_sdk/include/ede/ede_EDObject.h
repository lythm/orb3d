#pragma once

#include "ede_event.h"

namespace orb
{
	namespace ede
	{
		struct Event;

		class EventQueue;

		class EDObject
		{
		public:
			EDObject(const EDObjectId& id);
			virtual ~EDObject(void);

			const EDObjectId&			GetId();
			void						SetId(const EDObjectId& id);
		protected:
			EDObjectId					m_id;

			EventQueue*					m_pQueue;
		};
	}
}
