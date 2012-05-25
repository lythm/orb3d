
dofile(".\\assets\\common\\bot_app.lua");
dofile(".\\assets\\protocol\\protocol_elementia.lua");

Mod_Login_Class = 
{
	event_on_login_result = nil,
	
	_app = nil;


}

function Mod_Login_Class:Login(acc_name, pwd)
	assert(acc_name);
	assert(pwd);

	local login_packet = Protocol_Elementia.Packet_C2S_Login(acc_name, pwd);

	Bot_SendPacket(login_packet);

end

function Mod_Login_Class:OnPacket_LoginResult(packet)
	
	packet:Seek(8);
	local result  = packet:ReadByte();
	
	if self.event_on_login_result ~= nil then
		self.event_on_login_result(_app, result);
	end
end
function Mod_Login_Class:Install(app)
	
	_app = app;

	app:AddPacketHandler(S_2_C_LOGIN_RESULT, self, self.OnPacket_LoginResult);

end

function Mod_Login()
	
	return CreateObject(Mod_Login_Class);
	
end
