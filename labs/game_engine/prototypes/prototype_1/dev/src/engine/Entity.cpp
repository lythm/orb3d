#include "engine_pch.h"
#include "..\..\include\engine\Entity.h"

namespace engine
{
	Entity::Entity(void)
	{
	}


	Entity::~Entity(void)
	{
	}

	void Entity::AddComponent(const std::string& name, boost::shared_ptr<EntityComponent> pCom)
	{
		m_Coms[name] = pCom;
	}
	boost::shared_ptr<EntityComponent> Entity::FindComponent(const std::string& name)
	{
		return m_Coms[name];
	}

}
