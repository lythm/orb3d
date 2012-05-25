using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Net;
using System.Configuration;

namespace WIS
{
	class GSHost
	{

		Socket FAcceptSock;

		GSSessionManager FSessionManager;

		
		public bool Open()
		{
			
			string listener_addr = ConfigurationSettings.AppSettings["listener_addr"];
			
			string listener_port = ConfigurationSettings.AppSettings["listener_port"];
			
			string session_count = ConfigurationSettings.AppSettings["session_count"];

			
			
			FSessionManager = new GSSessionManager(Convert.ToInt32(session_count), 1);


			FAcceptSock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);


			IPAddress addr = IPAddress.Parse(listener_addr);

			IPEndPoint ep = new IPEndPoint(addr, Convert.ToInt32(listener_port));


			FAcceptSock.Bind(ep);

			FAcceptSock.Listen(1000);

			Accept();
	
			return true;
		}
		public void Close()
		{
			

			FAcceptSock.Close();


			FAcceptSock = null;

			

		}
		private void Accept()
		{
			
			string session_count = ConfigurationSettings.AppSettings["session_count"];

			for (int i = 0; i < Convert.ToInt32(session_count); ++i)
			{

				GSSession s = FSessionManager.AllocSession();

				s.OnClose += OnSessionClose;

				s.Accept(FAcceptSock);

			}
		}

		private void OnSessionClose(GSSession session)
		{
			session.Accept(FAcceptSock);
		}

	}
}
