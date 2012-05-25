
dofile(".\\assets\\common\\bot_app.lua");
dofile(".\\assets\\protocol\\protocol_elementia.lua");


Mod_Map_Class = 
{
	_app = nil,

	event_on_map_entered			= nil,
	event_on_map_correct			= nil,
}



function Mod_Map_Class:Install(app)
	
	self._app = app;

	app:AddPacketHandler(S_2_C_ABOUT_TO_ENTER, self, self.OnPacket_AboutToEnter);
	app:AddPacketHandler(S_2_C_MAP_ENTERED, self, self.OnPacket_MapEntered);

	app:AddPacketHandler(S_2_C_MAP_CORRECT, self, self.OnPacket_MapCorrect);
	
end

function Mod_Map_Class:OnPacket_MapCorrect(packet)
	
	packet:Seek(8);

	local s = packet:ReadByte();
	local t = packet:ReadByte();
	local p = packet:ReadByte();
	local d = packet:ReadFloat();

	if self.event_on_map_correct ~= nil then
		self.event_on_map_correct(self._app, s, t, p, d);
	end
end

function Mod_Map_Class:OnPacket_MapEntered(packet)
	
	packet:Seek(8);

	local wp = packet:ReadByte();
	local instance_id = packet:ReadByte();

	if self.event_on_map_entered ~= nil then
		self.event_on_map_entered(self._app, wp, instance_id);
	end
end

function Mod_Map_Class:OnPacket_AboutToEnter(packet)
	local packet = Protocol_Elementia.Packet_C2S_ReadyToEnter();

	Bot_SendPacket(packet);
end

function Mod_Map_Class:MoveTo(src_wp, tar_wp, ds, preamble)
	
	local packet = Protocol_Elementia.Packet_C2S_MapMove(src_wp, tar_wp, ds, preamble);
	
	Bot_SendPacket(packet);

end



function Mod_Map()
	
	return CreateObject(Mod_Map_Class);
end

