#pragma once

class BattleSession;

class BattleSessionManager
{
public:
	BattleSessionManager(void);
	virtual ~BattleSessionManager(void);

	BattleSession*										AllocBattleSession();
	void												FreeBattleSession();

	BattleSession*										FindSession(int id);

	void												Update();

private:
	boost::unordered_map<int, BattleSession*>			m_sessions;
};



