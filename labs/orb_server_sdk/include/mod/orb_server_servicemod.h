#pragma once

#include "orb_server_interface.h"

#include <boost/uuid/uuid.hpp>


namespace orb
{

	class ServiceMod
	{
	public:
		ServiceMod(const boost::uuids::uuid& id)
		{
			m_id = id;
		}

		virtual bool						Install(Core* pCore)							= 0;
		virtual void						Uninstall()										= 0;

		const boost::uuids::uuid&			GetId()
		{
			return m_id;
		}

	protected:
		ServiceMod(){}
		virtual ~ServiceMod(){}

		boost::uuids::uuid					m_id;
	};

	class ServiceModClass
	{
	public:
		virtual ServiceMod*					CreateObject()									= 0;
		virtual void						DeleteObject(ServiceMod* pMod)					= 0;

	protected:
		ServiceModClass(){}
		virtual ~ServiceModClass(){}
	};

	typedef ServiceModClass* (*PTR_GET_MODCLASS)();

#define FUNC_GET_MODCLASS_NAME				"GetServiceModClass"
}

