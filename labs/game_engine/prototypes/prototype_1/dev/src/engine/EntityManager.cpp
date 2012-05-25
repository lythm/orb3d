#include "engine_pch.h"
#include "engine\EntityManager.h"
#include "engine\Entity.h"

namespace engine
{
	EntityManager::EntityManager(void)
	{
	}


	EntityManager::~EntityManager(void)
	{
	}
	boost::shared_ptr<Entity> EntityManager::CreateEntity()
	{
		boost::shared_ptr<Entity> ptr(new Entity());

		return ptr;
	}
	void EntityManager::DestroyEntity(boost::shared_ptr<Entity> pEntity)
	{
		pEntity.reset();

	}
}
