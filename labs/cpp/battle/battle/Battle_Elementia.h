#pragma once

#include "BattleClass.h"
#include "Battle.h"

namespace elementia
{
	class Battle_Elementia : public Battle
	{
	public:
		Battle_Elementia(void);
		virtual ~Battle_Elementia(void);

		bool									Init();
		void									Release();

		void									Update();

	private:





	};


	class BattleClass_Elementia : public BattleClass
	{
	public:
		enum
		{
			BATTLE_ELEMENTIA				= 0x00000001,
		};
		Battle*						AllocBattle()
		{
			return new Battle_Elementia;
		}
		void						FreeBattle(Battle* pBattle)
		{
			delete (Battle_Elementia*)pBattle;
		}

		int							ClassID()
		{
			return BATTLE_ELEMENTIA;
		}


	};
	


}
