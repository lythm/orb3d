


dofile(".\\assets\\common\\bot_app.lua");
dofile(".\\assets\\protocol\\protocol_elementia.lua");



Mod_Battle_Class = 
{
	_app						= nil, 

	event_on_init_battle		= nil,
	
	event_on_resume_from_battle = nil,

	move_delay					= 1000,
	move_recive_tick			= 0,

	in_action					= false,
}



function Mod_Battle()
	
	return CreateObject(Mod_Battle_Class);
end


function Mod_Battle_Class:Install(app)
	
	self._app = app;

	app:AddPacketHandler(S_2_C_MAP_INIT_BATTLE, self, self.OnPacket_InitBattle);
	app:AddPacketHandler(S_2_C_MAP_RELEASE_BATTLE, self, self.OnPacket_ReleaseBattle);
	app:AddPacketHandler(S_2_C_MAP_RESUME_FROM_BATTLE, self, self.OnPacket_ResumeFromBattle);
	app:AddPacketHandler(S_2_C_BATTLE_READY, self, self.OnPacket_Ready);

	app:AddPacketHandler(S_2_C_BATTLE_ACTION, self, self.OnPacket_Action);

	app:AddPacketHandler(S_2_C_MAP_BATTLE_RESULT, self, self.OnPacket_BattleResult);
	
end

function Mod_Battle_Class:Update()
	
	if self.in_action == true then
	
		local tick = Bot_GetTick();

		if (tick - self.move_delay) >= self.move_delay then
			local move = Protocol_Elementia.Packet_C2S_BattleMove(0, 1);
	
			Bot_SendPacket(move);

			self.in_action = false;
		end

	end
end

function Mod_Battle_Class:OnPacket_BattleResult(packet)
	
	print("battle result");

	local resume = Protocol_Elementia.Packet_C2S_BattleConfirm();

	Bot_SendPacket(resume);
end
function Mod_Battle_Class:OnPacket_Action(packet)
	
	packet:Seek(8);

	local player = packet:ReadUInt32();

	print("on action", player, _app.player_id);

	if player ~= _app.player_id then
		return;
	end

	self.in_action			= true;
	self.move_recive_tick	= Bot_GetTick();

end
function Mod_Battle_Class:OnPacket_Ready(packet)
	print("battle ready");

	local ready = Protocol_Elementia.Packet_C2S_BattleReady();

	Bot_SendPacket(ready);


end
function Mod_Battle_Class:OnPacket_InitBattle(packet)
	print("Battle Init");
	if self.event_on_init_battle ~= nil then
		self.event_on_init_battle(self._app);
	end
end

function Mod_Battle_Class:OnPacket_ReleaseBattle(packet)
	print("battle release");
end

function Mod_Battle_Class:OnPacket_ResumeFromBattle(packet)
	
	print("battle resume");

	if self.event_on_resume_from_battle ~= nil then
		self.event_on_resume_from_battle(self._app);
	end
end
