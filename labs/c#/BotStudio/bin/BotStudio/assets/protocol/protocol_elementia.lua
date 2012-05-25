
C_2_S_BASE									= 64;
S_2_C_BASE									= C_2_S_BASE + 2048;




S_2_C_GATE_STATE							= S_2_C_BASE + 2;
S_2_C_LOGIN_RESULT							= S_2_C_BASE + 0;

C_2_S_LOGIN									= C_2_S_BASE + 0;
C_2_S_GUEST_LOGIN							= C_2_S_BASE + 3;
-- C_2_S_BATTLE
C_2_S_BATTLE								= C_2_S_BASE + 255;

C_2_S_BATTLE_READY							= C_2_S_BATTLE + 0;
C_2_S_BATTLE_MOVE							= C_2_S_BATTLE + 1;
C_2_S_BATTLE_CASTSKILL						= C_2_S_BATTLE + 2;
C_2_S_BATTLE_USE_ITEM						= C_2_S_BATTLE + 3;
C_2_S_BATTLE_SURRENDER						= C_2_S_BATTLE + 4;
C_2_S_BATTLE_ACTION_BEGIN					= C_2_S_BATTLE + 5;
C_2_S_BATTLE_ACTION_END						= C_2_S_BATTLE + 6;
C_2_S_BATTLE_ACTION_TIMEOUT					= C_2_S_BATTLE + 7;


C_2_S_MAP									= 420;
C_2_S_MAP_READY_TO_ENTER					= C_2_S_MAP + 1;
C_2_S_MAP_ENTER_WORLD						= C_2_S_MAP + 2;

C_2_S_MAP_MOVE								= C_2_S_MAP + 3;
C_2_S_MAP_STOP								= C_2_S_MAP + 4;
C_2_S_MAP_OBJECT_MENU_REQUEST				= C_2_S_MAP + 5;
C_2_S_MAP_OBJECT_MENU_ITEM					= C_2_S_MAP + 6;


C_2_S_MAP_QUERY_INSTANCE					= C_2_S_MAP + 8;
C_2_S_MAP_SWITCH_INSTANCE					= C_2_S_MAP + 9;

C_2_S_MAP_ENCOUNTER_SPOT					= C_2_S_MAP + 10;
C_2_S_MAP_MOVE_CANCEL						= C_2_S_MAP + 11;
C_2_S_MAP_BATTLE_RESULT_CONFIRM				= C_2_S_MAP + 12;

C_2_S_MAP_ALLOC_TUTORIAL_BATTLE				= C_2_S_MAP + 13;
C_2_S_TUTORIAL_START						= C_2_S_MAP + 14;

C_2_S_BOT_PING								= 1233;

S_2_C_BOT_PONG								= 3003;


-- S_2_C_BATTLE
S_2_C_BATTLE								= S_2_C_BASE + 255;
S_2_C_BATTLE_READY							= S_2_C_BATTLE + 1;
S_2_C_BATTLE_START							= S_2_C_BATTLE + 2;
S_2_C_BATTLE_STATE							= S_2_C_BATTLE + 3;
S_2_C_BATTLE_ACTION							= S_2_C_BATTLE + 4;
S_2_C_BATTLE_PLAYER_STATE					= S_2_C_BATTLE + 5;
S_2_C_BATTLE_PLAYER_MOVE					= S_2_C_BATTLE + 6;
S_2_C_BATTLE_OVER							= S_2_C_BATTLE + 7;
S_2_C_BATTLE_PLAYER_QUIT					= S_2_C_BATTLE + 8;
S_2_C_BATTLE_CONVERT						= S_2_C_BATTLE + 9;
S_2_C_BATTLE_RESET							= S_2_C_BATTLE + 10;
S_2_C_BATTLE_INIT_INFO						= S_2_C_BATTLE + 11;
S_2_C_BATTLE_SKILL_INFO						= S_2_C_BATTLE + 23;
S_2_C_BATTLE_SKILL_STATE					= S_2_C_BATTLE + 24;
S_2_C_BATTLE_PLAYER_CASTSKILL				= S_2_C_BATTLE + 25;
S_2_C_BATTLE_PLAYER_ITEM_INFO				= S_2_C_BATTLE + 26;
S_2_C_BATTLE_EFFECT							= S_2_C_BATTLE + 27;
S_2_C_BATTLE_UPDATE_WAISTPACK				= S_2_C_BATTLE + 28;
S_2_C_BATTLE_USE_ITEM						= S_2_C_BATTLE + 29;

S_2_C_BATTLE_TUTORIAL_MOVE_HINT				= S_2_C_BATTLE + 30;
S_2_C_BATTLE_TUTORIAL_SKILL_HINT			= S_2_C_BATTLE + 31;
S_2_C_BATTLE_TUTORIAL_MSG					= S_2_C_BATTLE + 32;

S_2_C_BATTLE_BUFF_ADDED						= S_2_C_BATTLE + 33;
S_2_C_BATTLE_BUFF_REMOVED					= S_2_C_BATTLE + 34;
S_2_C_BATTLE_BUFF_UPDATED					= S_2_C_BATTLE + 35;

S_2_C_BATTLE_TURN_BEGIN						= S_2_C_BATTLE + 36;

S_2_C_BATTLE_VISUAL_EFFECT_TEXT				= S_2_C_BATTLE + 37;




S_2_C_LOGIN_RESULT							= 2112;
S_2_C_ACC_ENTERSERVER						= 2578;

S_2_C_CHAT_MSG								= 2580;

S_2_C_ACCOUNT_CREATE_CHAR_RESULT			= 2569;
S_2_C_ACCOUNT_INFO							= 2570;
S_2_C_ACCOUNT_DELETE_CHAR_RESULT			= 2571;

S_2_C_ABOUT_TO_ENTER						= 2469;

S_2_C_MAP_BASE								= 2468;

S_2_C_MAP_ENTERED							= 2470;
S_2_C_MAP_CORRECT							= 2477;
S_2_C_MAP_INIT_BATTLE						= S_2_C_MAP_BASE + 19;
S_2_C_MAP_RELEASE_BATTLE					= S_2_C_MAP_BASE + 20;
S_2_C_MAP_RESUME_FROM_BATTLE				= S_2_C_MAP_BASE + 21;
S_2_C_MAP_BATTLE_RESULT						= S_2_C_MAP_BASE + 22;

S_2_C_GUEST_REGISTERATION_PREPARED			= 3301;
S_2_C_GUEST_REGISTERED						= 3302;

S_2_C_ACTIVITY_ROOKIECARD_RESULT			= 3400;

C_2_S_GUEST_LOGIN							= 67;
C_2_S_GUEST_PREPARE_REGISTER				= 1133;
C_2_S_GUEST_REGISTERED						= 1134;

C_2_S_READY_TO_ENTER						= 421;
C_2_S_MAP_ENTER_WORLD						= 422;
C_2_S_MAP_MOVE								= 423;
C_2_S_MAP_STOP								= 424;


C_2_S_MSG									= 532;


C_2_S_ACCOUNT_CREATE_CHAR					= 521;
C_2_S_ACCOUNT_DELETE_CHAR					= 522;


C_2_S_ACTIVITY_ROOKIE_CARD					= 1281;

KEEP_ALIVE_ACK								= 4;
KEEP_ALIVE									= 0;

VERSION										= 0x01020000;


do
	if Protocol_Elementia == nil then
		Protocol_Elementia = {};
	end

end

function Protocol_Elementia.Packet_FillSize(packet)
	local length = packet:GetLength();
	packet:Seek(0);
	packet:WriteUInt32(length);
	packet:Seek(length);
end


function Protocol_Elementia.Packet_C2S_BattleConfirm()
	local packet = PacketStream()
	
	packet:WriteUInt32(0);
	packet:WriteUInt32(C_2_S_MAP_BATTLE_RESULT_CONFIRM);
	
	Protocol_Elementia.Packet_FillSize(packet);
	return packet;
end

function Protocol_Elementia.Packet_C2S_BattleReady()
	
	local packet = PacketStream()
	
	packet:WriteUInt32(0);
	packet:WriteUInt32(C_2_S_BATTLE_READY);
	
	Protocol_Elementia.Packet_FillSize(packet);
	return packet;
end

function Protocol_Elementia.Packet_C2S_BotPing()

	local packet = PacketStream()
	
	packet:WriteUInt32(0);
	packet:WriteUInt32(C_2_S_BOT_PING);
	
	Protocol_Elementia.Packet_FillSize(packet);
	return packet;
end

function Protocol_Elementia.Packet_C2S_BattleMove(src, tar)
	local packet = PacketStream()
	
	packet:WriteUInt32(0);
	packet:WriteUInt32(C_2_S_BATTLE_READY);
	
	packet:WriteByte(src);
	packet:WriteByte(tar);


	Protocol_Elementia.Packet_FillSize(packet);
	return packet;


end
function Protocol_Elementia.Packet_C2S_RookieCard(card)
	
	local packet = PacketStream()
	
	packet:WriteUInt32(0);
	packet:WriteUInt32(C_2_S_ACTIVITY_ROOKIE_CARD);
	packet:WriteString(card);

	Protocol_Elementia.Packet_FillSize(packet);
	
	return packet;


end

function Protocol_Elementia.Packet_C2S_EnterWorld(slot)
	local packet = PacketStream()
	
	packet:WriteUInt32(0);
	packet:WriteUInt32(C_2_S_MAP_ENTER_WORLD);
	packet:WriteByte(slot);
	
	Protocol_Elementia.Packet_FillSize(packet);
	return packet;
end

function Protocol_Elementia.Packet_C2S_CreateChar(slot, portrait_id, pro_id, name, sprite_id, gender)
	
	local packet = PacketStream()
	
	packet:WriteUInt32(0);
	packet:WriteUInt32(C_2_S_ACCOUNT_CREATE_CHAR);
	packet:WriteByte(slot);
	packet:WriteUInt32(portrait_id);
	packet:WriteByte(pro_id);
	packet:WriteFixedString(name, 20);
	packet:WriteUInt32(sprite_id);
	packet:WriteByte(gender);

	Protocol_Elementia.Packet_FillSize(packet);
	return packet;

end

function Protocol_Elementia.Packet_C2S_DelChar(slot)
	
	local packet = PacketStream()
	
	packet:WriteUInt32(0);
	packet:WriteUInt32(C_2_S_ACCOUNT_DELETE_CHAR);
	packet:WriteByte(slot);

	Protocol_Elementia.Packet_FillSize(packet);
	return packet;

end
function Protocol_Elementia.Packet_C2S_Login(acc, pwd)
	
	local login_packet = PacketStream();
				
	login_packet:WriteUInt32(0);
	login_packet:WriteUInt32(C_2_S_LOGIN);

	login_packet:WriteFixedString(acc, 20);
	
	login_packet:WriteString_MD5(pwd);

	login_packet:WriteUInt32(VERSION);

	Protocol_Elementia.Packet_FillSize(login_packet);

	return login_packet;

end

function Protocol_Elementia.Packet_C2S_ReadyToEnter()
	local ready_packet = PacketStream();
	
	ready_packet:WriteUInt32(0);
	ready_packet:WriteUInt32(C_2_S_READY_TO_ENTER);

	Protocol_Elementia.Packet_FillSize(ready_packet);

	return ready_packet;
end

function Protocol_Elementia.Packet_C2S_GuestPrepareRegister()
		
	local packet = PacketStream();
	
	packet:WriteUInt32(8);
	packet:WriteUInt32(C_2_S_GUEST_PREPARE_REGISTER);

	return packet;
end

function Protocol_Elementia.Packet_C2S_GuestRegistered()
	local packet = PacketStream();
	
	packet:WriteUInt32(8);
	packet:WriteUInt32(C_2_S_GUEST_REGISTERED);

	return packet;
end


function Protocol_Elementia.Packet_C2S_MapStop(waypoint)
	
	local packet = PacketStream();

	packet:WriteUInt32(0);
	packet:WriteUInt32(C_2_S_MAP_STOP);
	packet:WriteByte(waypoint);

	Protocol_Elementia.Packet_FillSize(packet);

	return packet;
end
function Protocol_Elementia.Packet_C2S_MapMove(src, tar, ds, preamble)
	local packet = PacketStream();

	packet:WriteUInt32(0);
	packet:WriteUInt32(C_2_S_MAP_MOVE);
	
	packet:WriteByte(src);
	packet:WriteByte(tar);
	packet:WriteByte(preamble);
	packet:WriteFloat(ds);

	Protocol_Elementia.Packet_FillSize(packet);

	return packet;

end