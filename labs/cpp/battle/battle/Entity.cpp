#include "StdAfx.h"
#include "Entity.h"


Entity::Entity(void)
{
}


Entity::~Entity(void)
{
}
void Entity::RegisterComponent(EntityComponent* pCom)
{
	if(pCom == NULL)
		return;

	int id = pCom->GetId();

	m_components[id] = pCom;
}
EntityComponent* Entity::GetComponent(int id)
{
	ComponentMap::iterator it = m_components.find(id);
	if(it == m_components.end())
		return NULL;

	return it->second;
}
void Entity::Update(int tick)
{
	event_update(tick);
}
void Entity::AddEventHandler_Update(const boost::function<void (int)>& handler)
{
	event_update.connect(handler);
}
void Entity::ClearComponents()
{
	m_components.clear();
}
