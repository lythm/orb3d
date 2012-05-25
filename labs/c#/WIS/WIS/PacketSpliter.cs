using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
namespace WIS
{
	class PacketSpliter
	{

		byte[] FExchangeBuffer;

		MemoryStream FPacketStream;

		BinaryReader FReader;


		public delegate void EventPacketDecoded(byte[] packet, int bytes);

		public EventPacketDecoded OnPacket { get; set; }


		public PacketSpliter()
		{

			FExchangeBuffer = new byte[1024 * 8];

			FPacketStream = new MemoryStream(1024 * 8);

			FReader = new BinaryReader(FPacketStream);

		}


		public void Reset()
		{

			FPacketStream.SetLength(0);

		}

		public bool Decode(byte[] data, int bytes)
		{

			if (AppendData(data, bytes) == false)
			{

				return false;

			}


			FPacketStream.Seek(0, SeekOrigin.Begin);


			while (true)
			{

				long bytesLeft = FPacketStream.Length - FPacketStream.Position;

				if (bytesLeft < 4)
				{

					break;

				}


				UInt32 packetBytes = FReader.ReadUInt32();


				FPacketStream.Seek(-4, SeekOrigin.Current);


				if (bytesLeft < packetBytes)
				{

					break;

				}


				byte[] packet = FReader.ReadBytes((int)packetBytes);


				if (OnPacket != null)
				{

					OnPacket(packet, (int)packetBytes);

				}

			}


			long left = FPacketStream.Length - FPacketStream.Position;

			FPacketStream.Read(FExchangeBuffer, 0, (int)left);

			FPacketStream.Seek(0, SeekOrigin.Begin);
			
			FPacketStream.SetLength(left);
			
			FPacketStream.Write(FExchangeBuffer, 0, (int)left);


			return true;

		}

		bool AppendData(byte[] data, int bytes)
		{

			FPacketStream.Write(data, 0, bytes);
			
			return true;

		}
	}
}
