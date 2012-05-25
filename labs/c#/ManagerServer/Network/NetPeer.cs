using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace OrbNet
{
	class NetPeer : INetworkPeer
	{
		public delegate void NetEvent_Connected(NetPeer peer);
		public delegate void NetEvent_Accepted(NetPeer peer);
		public delegate void NetEvent_Read(NetPeer peer);
		public delegate void NetEvent_Sent(NetPeer peer);
		public delegate void NetEvent_Error(NetPeer peer, string errorMessage);

		public NetEvent_Accepted OnAccepted { get; set; }
		public NetEvent_Connected OnConnected{get;set;}
		public NetEvent_Read OnRead { get; set; }
		public NetEvent_Sent OnSent { get; set; }
		public NetEvent_Error OnError { get; set; }


	}
}
