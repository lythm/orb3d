using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Net;
using System.Threading;
using LuaInterface;
using System.IO;
using System.Reflection;
using BotStudio.BotEngine.BotEvent;

namespace BotStudio
{
	namespace BotEngine
	{
		partial class  Bot
		{
			private BotManager FManager;
			private BotDescriptor FBotDesc;
			private Socket FSock;
			private BufferManager FBufferManager;
			private SocketAsyncEventArgs FConnArg;
			private SocketAsyncEventArgs FDisconnArg;
			private PacketSpliter FPacketSpliter;

			private Timer FTimer;

			private int FBotId;

			private object FLock = new object();
			private Lua FLua;
			private LuaTable FLuaEvent;
			private LuaFunction FLuaEventHandler;

			public Bot(BotManager manager,BotDescriptor BotDesc, int BotId)
			{
				FBotId = BotId;
				FManager = manager;
				FBotDesc = BotDesc;
				FBufferManager = new BufferManager();
				FBufferManager.Initialize(100, 100);

				FPacketSpliter = new PacketSpliter();

				FPacketSpliter.OnPacket += OnPacket;

				FConnArg = new SocketAsyncEventArgs();
				FConnArg.Completed += new EventHandler<SocketAsyncEventArgs>(IO_Completed);
				FConnArg.UserToken = this;
				FConnArg.RemoteEndPoint = FBotDesc.Host;
				
				FDisconnArg = new SocketAsyncEventArgs();
				FDisconnArg.Completed += new EventHandler<SocketAsyncEventArgs>(IO_Completed);
				FDisconnArg.UserToken = this;
				FDisconnArg.DisconnectReuseSocket = true;

				FSock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

				FTimer = new Timer(OnTimer);
			}
			public void EmmitBotCommand(BotCommand command)
			{
				lock (FLock)
				{
					if(FLua == null)
						return;

					EmmitBotEvent(new BotEvent_Command(command));
				}
				
			}
			public void Stop()
			{
				try
				{
					lock (FLock)
					{
						StopTimer();
						EmmitBotEvent(new BotEvent_Stop());
					}
				}
				catch (LuaException e)
				{
					WriteLog(e.Source + ": " + e.Message);
				}

				Disconnect();
			}
			public bool Start()
			{
				lock (FLock)
				{
					FLua = CreateLuaVM();

					FLua.DoFile(FBotDesc.Script);

					FLua.NewTable("BotEvent");
					FLuaEvent = FLua.GetTable("BotEvent");
					FLuaEventHandler = FLua.GetFunction("OnEvent");

					BotEvent_Start startEvent = new BotEvent_Start(FBotId);

					EmmitBotEvent(startEvent);

					return startEvent.ret_val;
				}
			}

			private void FreeEventArg(SocketAsyncEventArgs e)
			{
				FBufferManager.Free(e);
			}
			private SocketAsyncEventArgs AllocEventArg()
			{
				SocketAsyncEventArgs e = FBufferManager.Alloc();
				e.Completed += new EventHandler<SocketAsyncEventArgs>(IO_Completed);
				e.UserToken = this;
				
				return e;
			}

			private void ProcessDisconnected(SocketAsyncEventArgs e)
			{
				try
				{
					lock (FLock)
					{
						EmmitBotEvent(new BotEvent_ConnectionLost(e.SocketError.ToString()));
					}
				}
				catch (LuaException lua_e)
				{
					WriteLog(lua_e.Source + ": " + lua_e.Message);
				}
			}
			private void IO_Completed(object sender, SocketAsyncEventArgs e)
			{
			    switch(e.LastOperation)
			    {
			        case SocketAsyncOperation.Disconnect:
						ProcessDisconnected(e);
			            break;
			        case SocketAsyncOperation.Connect:
						ProcessConnected(e);
			            break;
			        case SocketAsyncOperation.Receive:
						ProcessRead(e);
			            break;
			        case SocketAsyncOperation.Send:

						break;
					default:
						throw new ArgumentException("The last operation completed on the socket was not a receive or send");
				}
			}
			private void ProcessConnectedFailed(SocketAsyncEventArgs e)
			{
				try
				{
					lock (FLock)
					{
						EmmitBotEvent(new BotEvent_ConnectionFailed(e.SocketError.ToString()));
					}
				}
				catch (LuaException lua_e)
				{
					WriteLog(lua_e.Source + ": " + lua_e.Message);
				}
			}
			private bool ProcessConnected(SocketAsyncEventArgs e)
			{
				if (e.SocketError != SocketError.Success)
				{
					ProcessConnectedFailed(e);
				
					return false;
				}

				try
				{
					lock (FLock)
					{
						EmmitBotEvent(new BotEvent_Connected());
					}
				}
				catch (LuaException lua_e)
				{
					WriteLog(lua_e.Source + ": " + lua_e.Message);
				}

								
				SocketAsyncEventArgs readArg = AllocEventArg();
				PostReadOP(readArg);
				return true;
			}
			private void ProcessRead(SocketAsyncEventArgs e)
			{
				if (e.SocketError != SocketError.Success || e.BytesTransferred == 0)
				{
					try
					{
						lock (FLock)
						{
							EmmitBotEvent(new BotEvent_ConnectionLost(e.SocketError.ToString()));
						}
					}
					catch (LuaException lua_e)
					{
						WriteLog(lua_e.Source + ": " + lua_e.Message);
					}
					FreeEventArg(e);
					
					return;
				}

				FPacketSpliter.Decode(e.Buffer, e.BytesTransferred);

				PostReadOP(e);
			}
			private void ProcessSend(SocketAsyncEventArgs e)
			{
				if (e.SocketError != SocketError.Success)
				{
					try
					{
						lock (FLock)
						{
							EmmitBotEvent(new BotEvent_ConnectionLost(e.SocketError.ToString()));
						}
					}
					catch (LuaException lua_e)
					{
						WriteLog(lua_e.Source + ": " + lua_e.Message);
					}
					FreeEventArg(e);

					return;
				}
			}
			
			private void PostSendOP(byte[] data, int bytes)
			{
				SocketAsyncEventArgs e = AllocEventArg();

				Buffer.BlockCopy(data, 0, e.Buffer, 0, bytes);
				e.SetBuffer(0, bytes);
				if (false == FSock.SendAsync(e))
				{

				}
			}
			private bool PostReadOP(SocketAsyncEventArgs e)
			{
				if (false == FSock.ReceiveAsync(e))
				{
					ProcessRead(e);
				}
				
				return true;
			}

			void OnPacket(byte[] data, int bytes)
			{
				try
				{
					lock (FLock)
					{
						EmmitBotEvent(new BotEvent_NetPacket(new PacketStream(data, 0, bytes)));
					}
				}
				catch (LuaException e)
				{
					WriteLog(e.Source + ": " + e.Message);
				}
			}

			void EmmitBotEvent(BotEvent.BotEvent e)
			{
				lock (FLock)
				{
					FLuaEventHandler.Call(new object[] { e });
				}
			}

			void OnTimer(object state)
			{
				try
				{
					lock (FLock)
					{
						EmmitBotEvent(new BotEvent_Timer());
					}
				}
				catch (LuaException e)
				{
					WriteLog(e.Source + ": " + e.Message);
				}
			}
		}
	}
}
