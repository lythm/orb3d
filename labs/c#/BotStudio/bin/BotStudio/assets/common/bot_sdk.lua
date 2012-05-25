
luanet.load_assembly("BotStudio");

dofile(".\\assets\\common\\bot_events.lua");

PacketStream = luanet.import_type("BotStudio.BotEngine.PacketStream");



function _Print(...)
	local varlist = {...};
	local n = #varlist;
			
	local message = "-lua: ";

	for index = 1, n do
		local val = varlist[index];

		if val == nil then

			message = message.."nil".."\t";
		else
			message = message..tostring(val).."\t";
		end
	end
	Bot_PrintLog(message);
end


print = _Print;






function CreateObject(class)
	local o = {};
	setmetatable(o, class);
	class.__index = class;
	return o;
end