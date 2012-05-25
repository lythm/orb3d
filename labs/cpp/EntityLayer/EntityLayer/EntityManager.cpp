#include "EntityManager.h"
#include "entity.h"

EntityManager::EntityManager(void)
{
}

EntityManager::~EntityManager(void)
{
}
Entity*	EntityManager::CreateEntity(int id)
{
	Entity* pEntity = new Entity;

	return pEntity;
}
void EntityManager::DestroyEntity(Entity* pEntity)
{
	delete pEntity;
}