#pragma once

class BattleSession;
class BattleClass;
#include "Battle.h"


class BattleManager
{
public:
		

	BattleManager(void);
	virtual ~BattleManager(void);

	void									Update();

	void									RegisterBattleClass(int id, BattleClass* pClass);

	BattlePtr								AllocBattle(int classid);
	

private:
	boost::unordered_map<int, BattleClass*>	m_battleClassMap;
};

