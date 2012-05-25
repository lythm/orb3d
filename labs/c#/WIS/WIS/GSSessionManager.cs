using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;

namespace WIS
{
	class GSSessionManager
	{

		private int FStockCount;

		private int FGrowth;

		private Object FLock;

		private List<GSSession> FSessionList;


		public GSSessionManager(int nStock, int nGrowth)
		{

			FLock = new Object();

			FStockCount = nStock;
			
			FGrowth = nGrowth;



			FSessionList = new List<GSSession>(nStock);

			for (int i = 0; i < nStock; ++i)
			{

				FSessionList.Add(new GSSession(this));

			}
		}


		public GSSession AllocSession()
		{

			lock (FLock)
			{

				if (FSessionList.Count == 0)
				{

					Grow(FGrowth);

				}


				GSSession session = FSessionList[0];

				FSessionList.RemoveAt(0);


				return session;

			}
			
		}
		public void FreeSession(GSSession session)
		{

			lock (FLock)
			{

				FSessionList.Add(session);

			}

		}

		private void Grow(int count)
		{

			for (int i = 0; i < count; ++i)
			{

				FSessionList.Add(new GSSession(this));

			}
		}
	}
}
