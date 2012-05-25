#include "ede_pch.h"
#include "ede_EDObject.h"


namespace orb
{
	namespace ede
	{

		EDObject::EDObject(const EDObjectId& id)
		{
			m_id				= id;
			m_pQueue			= NULL;
		}

		EDObject::~EDObject(void)
		{
		}

		const EDObjectId& EDObject::GetId()
		{
			return m_id;
		}
		void EDObject::SetId(const EDObjectId& id)
		{
			m_id = id;
		}
	}
}
