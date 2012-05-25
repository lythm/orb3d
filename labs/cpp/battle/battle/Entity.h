#pragma once

#include "boost/unordered_map.hpp"

#include "Entitycomponent.h"

#include "EventDispatcher.h"

#include "GameEvent.h"

class Entity
{
public:
	Entity(void);
	virtual ~Entity(void);

	typedef boost::unordered_map<int, EntityComponent*>			ComponentMap;	

	void														RegisterComponent(EntityComponent* pCom);

	EntityComponent*											GetComponent(int id);


	void														Update(int tick);

	void														AddEventHandler_Update(const boost::function<void (int)>& handler);

	void														ClearComponents();
private:
	boost::signal<void (int)>									event_update;

private:
	ComponentMap												m_components;

	EventDispatcher<GameEvent>									m_geDispatcher;
};

