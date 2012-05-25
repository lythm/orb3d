using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LuaInterface;
using System.Reflection;
using BotStudio.BotEngine.BotEvent;
using System.Net.Sockets;
using System.Net;
using System.Threading;
namespace BotStudio
{

	namespace BotEngine
	{
		partial class Bot
		{
			public UInt32 GetTick()
			{
				return (UInt32)System.Environment.TickCount;
			}
			public void StartTimer(int period)
			{
				FTimer.Change(period, period);
			}
			public void StopTimer()
			{
				FTimer.Change(Timeout.Infinite, 0);
			}
			public void ResetTimer(int period)
			{
				FTimer.Change(period, period);

			}
			public void WriteLog(string log)
			{
				if (FBotDesc.Silenced)
					return;
				AppContext.WriteLog(FBotDesc.Script + ": " + log);
			}
			
			private Lua CreateLuaVM()
			{
				Lua l = new Lua();
				Type t = GetType();
				MethodInfo m = t.GetMethod("WriteLog");
				l.RegisterFunction("Bot_PrintLog", this, m);

				m = t.GetMethod("Connect");
				l.RegisterFunction("Bot_Connect", this, m);

				m = t.GetMethod("Disconnect");
				l.RegisterFunction("Bot_Disconnect", this, m);

				m = t.GetMethod("SendPacket");
				l.RegisterFunction("Bot_SendPacket", this, m);

				m = t.GetMethod("StartTimer");
				l.RegisterFunction("Bot_StartTimer", this, m);

				m = t.GetMethod("ResetTimer");
				l.RegisterFunction("Bot_ResetTimer", this, m);

				m = t.GetMethod("StopTimer");
				l.RegisterFunction("Bot_StopTimer", this, m);

				m = t.GetMethod("GetTick");
				l.RegisterFunction("Bot_GetTick", this, m);

				return l;
			}

			public bool Connect()
			{
				
				if (false == FSock.ConnectAsync(FConnArg))
				{
					ProcessConnected(FConnArg);
				}

				return true;
			}
			public void Disconnect()
			{
				if (FSock == null)
					return;

				if (false == FSock.DisconnectAsync(FDisconnArg))
				{
					ProcessDisconnected(FDisconnArg);
				}
			}

			public void SendPacket(PacketStream packet)
			{
				PostSendOP(packet.GetBytes(), (int)packet.GetLength());
			}
		}
	}
}
