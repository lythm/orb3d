#pragma once

enum 
{
	GE_BATTLE_MOVE,

	GE_BATTLE_STARTED,
	GE_BATTLE_OVER,
	GE_BATTLE_RESULT,

	GE_ITEM_ADDED_TO_INVENTORY,
	GE_ITEM_REMOVED_FROM_INVENTORY,
	
	//GE_ITEM_DESTROYED,

	GE_BATTLE_SKILL_CASTING,
	GE_BATTLE_SKILL_CASTED,

	GE_BATTLE_SKILL_FAILED,


	GE_BATTLE_TURN_BEGIN,
	GE_BATTLE_TURN_END,

	GE_BATTLE_ACTION_BEGIN,
	GE_BATTLE_ACTION_END,

	GE_BOARD_GEM_DESTROYED,
	GE_BOARD_GEM_ELIMINATED,

	GE_BOARD_GEM_CONVERTED,
	GE_BOARD_GEM_GEN_IN_PLACE,

	GE_BOARD_RESET,

};
struct GameEvent
{
	int						id;
};



struct GameEvent_BattleStarted : public GameEvent
{

};

struct GameEvent_BattleMove : public GameEvent
{
	int							playerId;

};

struct GameEvent_BattleOver : public GameEvent
{

};



