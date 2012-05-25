dofile(".\\assets\\common\\bot_sdk.lua");

BotApp_Class = 
{
	packet_handlers = {},

	mods = {},
}


function BotApp_Class:OnStart(e)

end

function BotApp_Class:OnStop(e)

end

function BotApp_Class:OnConnected(e)

end

function BotApp_Class:OnConnectionLost(e)

end

function BotApp_Class:OnConnectingFailed(e)

end
function BotApp_Class:OnTimer(e)
	
end

function BotApp_Class:OnBotCommand(e)
	
	
end
function BotApp_Class:OnNetPacket(e)
	
	local packet = e.packet;

	local packet_bytes = packet:ReadUInt32();
	local packet_id = packet:ReadUInt32();

	packet:Seek(0);

	local handlers = self.packet_handlers[packet_id];

	if handlers == nil then
		
		print("unhandled packet:", packet_id);
		
		return;
	end

	for i, handler in ipairs(handlers) do
		

		local owner = handler.owner;
		local func = handler.handler;
	
		func(owner, packet);
	end
end


function BotApp_Class:GetModule(mod_name)
	
	return self.mods[mod_name];
end

function BotApp_Class:InstallModule(mod_name, m)
	
	m:Install(self);

	self.mods[mod_name] = m;

end

function BotApp_Class:AddPacketHandler(packet_id, owner, handler)
	
	assert(packet_id);
	assert(handler);
	assert(owner);
	assert(handler);

	if handler == nil then
		return;
	end

	if self.packet_handlers[packet_id] == nil then
		self.packet_handlers[packet_id] = {};
	end

	local handler_obj = {};
	handler_obj.owner = owner;
	handler_obj.handler = handler;

	table.insert(self.packet_handlers[packet_id], handler_obj);
end




function BotApp_Class:OnEvent(e)
	

	local handlers = 
	{
		[BOT_EVENT_ON_START] = self.OnStart,
		[BOT_EVENT_ON_STOP] = self.OnStop,
		[BOT_EVENT_ON_CONNECTED] = self.OnConnected,
		[BOT_EVENT_ON_CONNECTION_LOST] = self.OnConnectionLost,
		[BOT_EVENT_ON_CONNECTING_FAILED]  = self.OnConnectingFailed,
		[BOT_EVENT_ON_NET_PACKET] = self.OnNetPacket,
		[BOT_EVENT_ON_TIMER] = self.OnTimer,
		[BOT_EVENT_ON_COMMAND] = self.OnBotCommand
	}
	
	local handler = handlers[e.id];

	if handler ~= nil then
		handler(self, e);
	end

end


function BotApp()
	
	return CreateObject(BotApp_Class);
end
