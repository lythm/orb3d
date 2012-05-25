using System;
using System.Collections.Generic;

using System.Text;
using System.Net.Sockets;
namespace BotStudio
{
	namespace BotEngine
	{

		class BufferManager
		{
			private int FGrowth;
			private List<SocketAsyncEventArgs> FBuffers;


			public BufferManager()
			{
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
				if (FBuffers.Count == 0)
				{
					Grow(FGrowth);
				}

				int index = FBuffers.Count - 1;

				SocketAsyncEventArgs buffer = FBuffers[index];

				FBuffers.RemoveAt(index);

				return buffer;
			}
			public void Free(SocketAsyncEventArgs buffer)
			{
				if (FBuffers.Count >= FBuffers.Capacity)
				{
					FBuffers.Capacity += FGrowth;
				}

				FBuffers.Add(buffer);
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

}