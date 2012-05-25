


dofile(".\\assets\\common\\bot_app.lua");
dofile(".\\assets\\protocol\\protocol_elementia.lua");



Mod_Chat_Class = 
{
	_app = nil,

}


function Mod_Chat()
	
	return CreateObject(Mod_Chat_Class);
end

function Mod_Chat_Class:Install(app)
	
	self._app = app;

	app:AddPacketHandler(S_2_C_CHAT_MSG, self, self.OnPacket_S2C_ChatMsg);
	
end

function Mod_Chat_Class:OnPacket_S2C_ChatMsg(packet)

	packet:Seek(8);

	local t = packet:ReadByte();
	local gender = packet:ReadByte();
	local fb = packet:ReadByte();
	local name = packet:ReadFixedString(20);

	local element_count = packet:ReadUInt32();

	if element_count == 0 then
		return;
	end


	local element_id = packet:ReadUInt32();
	local clr = packet:ReadUInt32();


	if element_id ~= 0 then
		print("[hyper-link: "..element_id.." ]");
		return;
	end
	
	local msg = packet:ReadString();

	print(name.." says: ".. msg);
		
end

function Mod_Chat_Class:SendChatMsg(msg)
	
end