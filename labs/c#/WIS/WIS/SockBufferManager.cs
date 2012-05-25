using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
namespace WIS
{
	class SockBufferManager
	{
		private object FLock;
		private int FGrowth;

		private List<SocketAsyncEventArgs> FBuffers;


		public SockBufferManager()
		{
			FLock = new object();
		}


		private SocketAsyncEventArgs NewBuffer()
		{

			SocketAsyncEventArgs e = new SocketAsyncEventArgs();

			e.SetBuffer(new byte[1024], 0, 1024);


			return e;

		}


		public bool Initialize(int nInitCount, int nGrowth)
		{

			FBuffers = new List<SocketAsyncEventArgs>(nInitCount);


			FGrowth = nGrowth;



			for (int i = 0; i < nInitCount; ++i)
			{

				FBuffers.Add(NewBuffer());

			}

			return true;

		}
		public SocketAsyncEventArgs Alloc()
		{
			lock (FLock)
			{
				if (FBuffers.Count == 0)
				{

					Grow(FGrowth);

				}


				int index = FBuffers.Count - 1;

				SocketAsyncEventArgs buffer = FBuffers[index];


				FBuffers.RemoveAt(index);


				buffer.SetBuffer(0, 1024);

				return buffer;
			}
		}
		public void Free(SocketAsyncEventArgs buffer)
		{

			lock (FLock)
			{

				if (FBuffers.Count >= FBuffers.Capacity)
				{

					FBuffers.Capacity += FGrowth;

				}


				FBuffers.Add(buffer);
			}

		}

		private void Grow(int nGrowth)
		{

			for (int i = 0; i < nGrowth; ++i)
			{

				FBuffers.Add(NewBuffer());

			}

		}
	}
}
