#pragma once

class Entity;
class EntityTemplate
{
public:
	EntityTemplate(void){}
	virtual ~EntityTemplate(void){};

	virtual Entity*							CreateEntity()							= 0;
	virtual void							DestroyEntity(Entity* pEntity)			= 0;
};
