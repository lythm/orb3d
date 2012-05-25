using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LuaInterface;
using System.IO;

namespace BotStudio
{
	namespace BotEngine
	{
		namespace BotEvent
		{
			class BotEvent
			{
				public BotEvent()
				{
					
				}
				public enum EventID
				{
					BOT_EVENT_ON_START,
					BOT_EVENT_ON_STOP,
					BOT_EVENT_ON_CONNECTED,
					BOT_EVENT_ON_CONNECTION_LOST,
					BOT_EVENT_ON_CONNECTING_FAILED,
					BOT_EVENT_ON_NET_PACKET,
					BOT_EVENT_ON_TIMER,
					BOT_EVENT_ON_COMMAND,
				}

				public int id {get;set;}
				
			}

			class BotEvent_Start : BotEvent
			{
				public bool ret_val{get;set;}
				public int bot_id { get; set; }
				
				public BotEvent_Start(int botId)
				{
					bot_id = botId;
					id = (int)EventID.BOT_EVENT_ON_START;
				}
			}

			class BotEvent_Stop : BotEvent
			{
				public BotEvent_Stop()
				{
					id = (int)EventID.BOT_EVENT_ON_STOP;
				}
			}
			class BotEvent_Connected : BotEvent
			{
				public BotEvent_Connected()
				{
					id = (int)EventID.BOT_EVENT_ON_CONNECTED;
				}
				
			}

			class BotEvent_ConnectionFailed : BotEvent
			{
				public string error_message{get;set;}
				
				public BotEvent_ConnectionFailed(string errorMsg)
				{
					error_message = errorMsg;
					id = (int)EventID.BOT_EVENT_ON_CONNECTING_FAILED;
				}

			}

			class BotEvent_ConnectionLost : BotEvent
			{
				public string error_message{get;set;}

				public BotEvent_ConnectionLost(string error)
				{
					error_message = error;
					id = (int)EventID.BOT_EVENT_ON_CONNECTION_LOST;
				}
			}
			
			class BotEvent_NetPacket : BotEvent
			{
				public PacketStream packet;

				public BotEvent_NetPacket(PacketStream PacketData)
				{
					packet = PacketData;
					id = (int)EventID.BOT_EVENT_ON_NET_PACKET;
				}
			}

			class BotEvent_Timer : BotEvent
			{
				public BotEvent_Timer()
				{
					id = (int)EventID.BOT_EVENT_ON_TIMER;
				}
			}
			class BotEvent_Command : BotEvent
			{
				public string command { get; set; }
				public Dictionary<string, string> parameters{get;set;}


				public BotEvent_Command(BotCommand cmd)
				{
					command = cmd.CommandName;
					id = (int)EventID.BOT_EVENT_ON_COMMAND;

					parameters = new Dictionary<string, string>();

					foreach (BotCommand.Parameter param in cmd.Parameters)
					{
						parameters[param.Name] = param.Value;
					}
		
				}
			}
		}
	}
}