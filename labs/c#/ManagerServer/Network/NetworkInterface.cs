using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace OrbNet
{
	public class Network
	{
		public bool Initialize(int peerStockCount)
		{
			return true;
		}
		public void Release()
		{
		}

		public INetworkPeer CreatePeer()
		{
			return new NetPeer();
		}
	}
}
