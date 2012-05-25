#pragma once

class BattleEngine;

class Battle
{
public:
	Battle(){}
	virtual ~Battle(){}


	virtual void						Update(){}

	
	void								ProcessBattle();
	
	void								AddEventHandler(int id, const boost::function<void (void*)>& handler); 

private:
	bool								InitBattle();
	void								ReleaseBattle();


private:
	

	BattleEngine*						m_pEngine;
	

};

typedef boost::shared_ptr<Battle>		BattlePtr;
