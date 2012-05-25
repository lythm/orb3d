dofile(".\\assets\\common\\bot_app.lua");
dofile(".\\assets\\protocol\\protocol_elementia.lua");


Mod_KeepAlive_Class = 
{
}


function Mod_KeepAlive()

	return CreateObject(Mod_KeepAlive_Class);

end
function Mod_KeepAlive_Class:OnPacket_KeepAlive(packet)

	local keep_alive = PacketStream();

	keep_alive:WriteUInt32(8);
	keep_alive:WriteUInt32(KEEP_ALIVE_ACK);

	Bot_SendPacket(keep_alive);

	print("keeping alive");

end
function Mod_KeepAlive_Class:Install(app)
	
	_app = app;

	app:AddPacketHandler(KEEP_ALIVE, self, self.OnPacket_KeepAlive);

end


