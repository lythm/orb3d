#pragma once

class Battle;

class BattleClass
{
public:

	virtual Battle*						AllocBattle()									= 0;
	virtual void						FreeBattle(Battle* pBattle)						= 0;

	virtual int							ClassID()										= 0;

	

protected:
	BattleClass(void){}

	virtual ~BattleClass(void){}
};

