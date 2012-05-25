#pragma once


class BattleUnit;
class Battle;
class LobbyServer;

class BattleSession
{
public:
	BattleSession(void);
	virtual ~BattleSession(void);

	void							Open();
	void							Release();

	void							Update();


private:
	Battle*							m_pBattle;
	
	std::vector<BattleUnit*>		m_units;

	LobbyServer*					m_pLobby;

	int								m_roomid;
};

