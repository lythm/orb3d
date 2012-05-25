

dofile(".\\assets\\common\\bot_app.lua");
dofile(".\\assets\\protocol\\protocol_elementia.lua");

-- 职业id
PRO_ID_ALL                              = 0;            -- 全职业
PRO_ID_WAR								= 1;			-- 战士
PRO_ID_DRU								= 2;			-- 德鲁伊
PRO_ID_WIZ								= 3;			-- 法师
PRO_ID_KNI								= 4;			-- 骑士

Mod_Account_Class = 
{
	char_type = 
	{
		[0] = 
		{
			gender		= 1,
			portraitId	= 0x01010000,
			sprite		= 0x02010000,
			proId		= PRO_ID_WAR,
		},
		
		[1] = 
		{
			gender		= 2,
			portraitId	= 0x01010100,
			sprite		= 0x02010100,
			proId		= PRO_ID_WAR,
		},

		[2] = 
		{
			gender		= 1,
			portraitId	= 0x01020000,
			sprite		= 0x02020000,
			proId		= PRO_ID_DRU,
		},

		[3] = 
		{
			gender		= 2,
			portraitId	= 0x01020100,
			sprite		= 0x02020100,
			proId		= PRO_ID_DRU,
		},

		[4] = 
		{
			gender		= 1,
			portraitId	= 0x01030000,
			sprite		= 0x02030000,
			proId		= PRO_ID_WIZ,
		},

		[5] = 
		{
			gender		= 2,
			portraitId	= 0x01030100,
			sprite		= 0x02030100,
			proId		= PRO_ID_WIZ,
		},

		[6] = 
		{
			gender		= 1,
			portraitId	= 0x01040000,
			sprite		= 0x02040000,
			proId		= PRO_ID_KNI,
		},

		[7] =
		{
			gender		= 2,
			portraitId	= 0x01040100,
			sprite		= 0x02040100,
			proId		= PRO_ID_KNI,
		},
	},
	
	_app = nil,
	acc_info = {},

	event_on_server_entered			= nil,
	event_on_account_info			= nil,
	event_on_delete_char_result		= nil,
	event_on_create_char_result		= nil,
	

	player_id = nil,
}


function Mod_Account()
	
	return CreateObject(Mod_Account_Class);
end


function Mod_Account_Class:Install(app)
	
	self._app = app;

	app:AddPacketHandler(S_2_C_ACC_ENTERSERVER, self, self.OnPacket_ServerEntered);
	app:AddPacketHandler(S_2_C_ACCOUNT_INFO, self, self.OnPacket_AccountInfo);
	app:AddPacketHandler(S_2_C_ACCOUNT_DELETE_CHAR_RESULT, self, self.OnPacket_DeleteCharResult);
	app:AddPacketHandler(S_2_C_ACCOUNT_CREATE_CHAR_RESULT, self, self.OnPacket_CreateCharResult);
	
end

function Mod_Account_Class:OnPacket_AccountInfo(packet)

	packet:Seek(8);
	local acc_info = {};
	acc_info.char_count = packet:ReadByte();
	acc_info.chars = {};
	for i = 1, acc_info.char_count do
		local char_info = {};
		
		char_info.slot			= packet:ReadByte();
		char_info.portrait		= packet:ReadUInt32();
		char_info.pro			= packet:ReadUInt32();
		char_info.name			= packet:ReadFixedString(20);
		

		char_info.lvl			= packet:ReadUInt32();
		char_info.sprite		= packet:ReadUInt32();

		table.insert(acc_info.chars, char_info);
	end
	
	self.acc_info = acc_info;

	if self.event_on_account_info ~= nil then
		self.event_on_account_info(self._app, self.acc_info);
	end
end

function Mod_Account_Class:OnPacket_ServerEntered(packet)
	packet:Seek(8);

	self.player_id = packet:ReadUInt32();
	if self.event_on_server_entered ~= nil then
		self.event_on_server_entered(self._app, self.player_id);
	end
end

function Mod_Account_Class:OnPacket_DeleteCharResult(packet)
	
	packet:Seek(8);

	local slot = packet:ReadByte();
	local result = packet:ReadByte();

	if result == 0 then
		self.acc_info.chars[slot] = nil;
	end

	if self.event_on_delete_char_result ~= nil then
		self.event_on_delete_char_result(self._app, slot, result);
	end
end

function Mod_Account_Class:DeleteChar(slot)
	local packet = Protocol_Elementia.Packet_C2S_DelChar(slot);
	Bot_SendPacket(packet);
end



function Mod_Account_Class:OnPacket_CreateCharResult(packet)
	
	packet:Seek(8);
	local slot = packet:ReadByte();
	local result = packet:ReadByte();

	if self.event_on_create_char_result ~= nil then
		self.event_on_create_char_result(self._app, slot, result);
	end
end

function Mod_Account_Class:CreateChar(slot, name, char_type_id)
	
	local char_type = self.char_type[char_type_id];

	if char_type == nil then
		return;
	end

	local packet = Protocol_Elementia.Packet_C2S_CreateChar(slot, char_type.portraitId, char_type.proId, name, char_type.sprite, char_type.gender);

	Bot_SendPacket(packet);
end

function Mod_Account_Class:EnterWorld(slot)
	
	local packet = Protocol_Elementia.Packet_C2S_EnterWorld(slot);

	Bot_SendPacket(packet);

end
