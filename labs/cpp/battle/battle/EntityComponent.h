#pragma once
class Entity;

class EntityComponent
{
public:
	EntityComponent(void);
	virtual ~EntityComponent(void);


	virtual int									GetId()							= 0;
private:

	
};

