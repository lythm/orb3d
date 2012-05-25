#pragma once



class Entity;

class EntityManager
{
public:
	EntityManager(void);
	virtual ~EntityManager(void);

	Entity*								CreateEntity(int id);
	void								DestroyEntity(Entity* pEntity);

private:

};
