using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Diagnostics;

namespace WIS
{
	partial class GSSession
	{

		SessionPacketHandler FPacketHandler;

		Socket FSock;

		SocketAsyncEventArgs FAcceptEventArg;

		PacketSpliter FPacketSpliter;
		
		GSSessionManager FSessionManager;

		SockBufferManager FBufferManager;


		public delegate void CloseEventHandler(GSSession session);

		public CloseEventHandler OnClose{get;set;}

		public GSSession(GSSessionManager manager)
		{

			FSessionManager = manager;


			FPacketHandler = new SessionPacketHandler(this);
			
			
			FPacketSpliter = new PacketSpliter();
			
			FPacketSpliter.OnPacket += FPacketHandler.OnPacket; ;

			
			FSock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
			
			
			FAcceptEventArg = new SocketAsyncEventArgs();
			
			FAcceptEventArg.AcceptSocket = FSock;
			
			FAcceptEventArg.Completed += OnCompleted;
			
			FAcceptEventArg.UserToken = this;


			FBufferManager = new SockBufferManager();
			
			FBufferManager.Initialize(10, 10);


		}



		~GSSession()
		{

			FSock.Close();

		}


		public void Accept(Socket ListenSock)
		{

			if (false == ListenSock.AcceptAsync(FAcceptEventArg))
			{

				OnCompleted(ListenSock, FAcceptEventArg);

			}

		}


		public bool Open()
		{

			FPacketSpliter.Reset();


			return true;

		}

		public void Close()
		{

			FSock.Disconnect(true);

			OnClose(this);

		}
		

		void OnCompleted(object sender, SocketAsyncEventArgs e)
		{

			switch (e.LastOperation)
			{

				case SocketAsyncOperation.Accept:
					
					ProcessAccept(sender, e);
					
					break;


				case SocketAsyncOperation.Receive:
					
					ProcessRead(sender, e);
					
					break;


				case SocketAsyncOperation.Send:
					
					ProcessSend(sender, e);
					
					break;


				case SocketAsyncOperation.Disconnect:
					
					ProcessLost(sender, e);
					
					break;


				default:
					
					ProcessError(sender, e);
					
					break;

			}

		}


		void ProcessError(object sender, SocketAsyncEventArgs e)
		{

			EventLog.WriteEntry("WIS", e.SocketError.ToString(), EventLogEntryType.Error);

			Console.WriteLine(e.SocketError.ToString());


		}


		void ProcessAccept(object sender, SocketAsyncEventArgs e)
		{

			if (e.SocketError != SocketError.Success)
			{
				ProcessError(sender, e);
				
				FSessionManager.FreeSession(this);
				
				return;
			}

			
			Console.WriteLine("GameServer Connected[{0}].", e.AcceptSocket.RemoteEndPoint.ToString());


			GSSession session = (GSSession)e.UserToken;

			session.Open();


			SocketAsyncEventArgs readEvent = AllocArgEvent();

			ReadData(readEvent);

		}


		void ProcessLost(object sender, SocketAsyncEventArgs e)
		{

			ProcessError(sender, e);


			FreeArgEvent(e);


			Console.WriteLine("GameServer[{0}] Lost", FSock.RemoteEndPoint.ToString());

			Close();

			FSessionManager.FreeSession(this);

		}


		void ProcessRead(object sender, SocketAsyncEventArgs e)
		{

			if (e.SocketError != SocketError.Success)
			{

				ProcessLost(sender, e);
				
				return;

			}

			try
			{

				FPacketSpliter.Decode(e.Buffer, e.BytesTransferred);
			}
			catch (Exception exception)
			{
				Console.WriteLine(exception.Message);
				ProcessLost(sender, e);
				return;
			}

			ReadData(e);

		}
		void ProcessSend(object sender, SocketAsyncEventArgs e)
		{

			if (e.SocketError != SocketError.Success)
			{
				ProcessLost(sender, e);

				FreeArgEvent(e);

				return;

			}


			FreeArgEvent(e);

		}

		SocketAsyncEventArgs AllocArgEvent()
		{

			 SocketAsyncEventArgs e = FBufferManager.Alloc();

			e.Completed += OnCompleted;

			e.UserToken = this;

			
			return e;

		}

		void FreeArgEvent(SocketAsyncEventArgs e)
		{

			e.UserToken = null;

			e.SetBuffer(0, 1024);

			e.Completed -= OnCompleted;



			FBufferManager.Free(e);
		}


		void ReadData(SocketAsyncEventArgs e)
		{

			if (false == FSock.ReceiveAsync(e))
			{

				ProcessRead(this, e);

			}

		}
		void SendPacket(PacketStream packet)
		{

			SendData(packet.GetBytes(), (int)packet.GetLength());

		}
		void SendData(byte[] data, int bytes)
		{
			SocketAsyncEventArgs e = AllocArgEvent();


			if (bytes > e.Buffer.Length)
			{
				byte[] buffer = new byte[bytes];
				e.SetBuffer(buffer, 0, bytes);
			}
			

			Buffer.BlockCopy(data, 0, e.Buffer, 0, bytes);

			e.SetBuffer(0, bytes);


			if (false == FSock.SendAsync(e))
			{

				ProcessSend(this, e);

			}

		}
	}
}

