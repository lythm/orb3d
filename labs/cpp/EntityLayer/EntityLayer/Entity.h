#pragma once
#include <vector>

class EntityProperty;
class Entity
{
public:
	Entity(void);
	virtual ~Entity(void);

private:
	std::vector<EntityProperty*>				m_props;
};

