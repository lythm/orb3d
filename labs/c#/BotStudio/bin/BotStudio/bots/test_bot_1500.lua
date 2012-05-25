
dofile(".\\assets\\common\\bot_app.lua");
dofile(".\\assets\\protocol\\protocol_elementia.lua");


dofile(".\\assets\\mods\\all.lua");








BotCommandList = 
{
	["Move"]  = 
	{
		"src_wp", "tar_wp",
	},
	["Stop"] = 
	{
	},

	["UseRookieCard"] = 
	{
	},
}




TestBot = BotApp();


TestBot.bot_id = -1;
TestBot.player_id = -1;
TestBot.waypoint = 0xff;
TestBot.Battling = false;

function TestBot:InstallModules()
	
	local m = Mod_KeepAlive();
	self:InstallModule("mod_keepalive", m);
	
	m = Mod_Login();

	m.event_on_login_result = self.OnLoginResult;

	self:InstallModule("mod_login", m);

	m = Mod_Account();
	
	m.event_on_server_entered		= TestBot.OnServerEntered;
	m.event_on_account_info			= TestBot.OnAccInfo;
	m.event_on_create_char_result	= TestBot.OnCreatCharResult;

	self:InstallModule("mod_account", m);

	m = Mod_Chat();
	self:InstallModule("mod_chat", m);


	m = Mod_Map();

	m.event_on_map_entered			= TestBot.OnMapEntered;
	m.event_on_map_correct			= TestBot.OnMapCorrect;
	self:InstallModule("mod_map", m);

	m = Mod_Battle();

	m.event_on_init_battle			= TestBot.OnBattleInit;
	m.event_on_resume_from_battle	= TestBot.OnResumeBattle;

	self:InstallModule("mod_battle", m);

end
function TestBot:OnStart(e)

	self.bot_id = e.bot_id;
	e.ret_val = true;

	self:AddPacketHandler(S_2_C_GATE_STATE, self, self.OnGateState);
	self:AddPacketHandler(S_2_C_BOT_PONG, self, self.OnBotPong);
	self:AddPacketHandler(S_2_C_ACTIVITY_ROOKIECARD_RESULT, self, self.OnRookieCardResult);
	self:InstallModules();
	Bot_Connect();

end

function TestBot:OnBattleInit()
	
	self.Battling = true;

end

function TestBot:OnResumeBattle()
	
	self.Battling = false;
	

end

function TestBot:OnRookieCardResult(packet)

	local bytes = packet:ReadUInt32();
	local id = packet:ReadUInt32();

	local ret = packet:ReadByte();

	print("rookie card result: "..ret);
	
end

function TestBot:OnBotCommand(e)
	
	if e.command == "Move" then
		local m = self:GetModule("mod_map");
		m:MoveTo(self.waypoint, 10, 0, 0xff);
		return;
	end


	if e.command == "UseRookieCard" then
		
		local packet = Protocol_Elementia.Packet_C2S_RookieCard("xs0001022139161173")

		Bot_SendPacket(packet);
		return;
		
	end

	print("Bot Command: "..e.command);	
end

function TestBot:OnBotPong(packet)
	
	local tick = Bot_GetTick();

	tick = tick - TestBot.tick;

	print("pintg time:", tick, TestBot.tick );
end	

function TestBot:OnTimer(e)

	if self.Battling == false then

		local m = self:GetModule("mod_map");

		local t = math.random(0, 30);

		m:MoveTo(self.waypoint, t, 0, 0xff);

		return;
	end


	
	local m = self:GetModule("mod_battle");

	m:Update();

end

function TestBot:OnLoginResult(result)
	if result ~= 0 then

		print("login failed", result);
		return;
	end

	local m = self:GetModule("mod_account");

	print("logged in");

	local packet = Protocol_Elementia.Packet_C2S_BotPing();

	TestBot.tick = Bot_GetTick();
--	Bot_SendPacket(packet);

end

function TestBot:OnCreatCharResult(slot , result)

	local m = self:GetModule("mod_account");

	print("create Char Result: ", result);

	m:EnterWorld(0);
end

function TestBot:OnGateState(packet)
	
	local login_mod = self:GetModule("mod_login");

	login_mod:Login("Bot"..(self.bot_id + 1500), "111111");

	--login_mod:Login("gguha1104", "111111");

end

function TestBot:OnServerEntered(player_id)
	
	self.player_id = player_id;
	print("server entered. player_id: ", player_id);
end

function TestBot:OnAccInfo(acc_info)
	
	print(acc_info.char_count);

	for i, char_info in ipairs(acc_info.chars) do
		
		print(char_info.name, char_info.slot, char_info.portrait, char_info.pro, char_info.lvl, char_info.sprite);
	end

	local m = self:GetModule("mod_account");

	if acc_info.char_count == 0 then
		m:CreateChar(0, "Bot"..self.bot_id, math.random(1, 7));
	else
		m:EnterWorld(0);
	end
end


function TestBot:OnMapEntered(waypoint, instance_id)
	
	print("Map entered:", waypoint, instance_id);

	self.waypoint = waypoint;

	Bot_ResetTimer(2000);
	
end

function TestBot:OnMapCorrect(s, t, p, d)
	
	self.waypoint = t;

end
function OnEvent(e)
	
	TestBot:OnEvent(e);
end


