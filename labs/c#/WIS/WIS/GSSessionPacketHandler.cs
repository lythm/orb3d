using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace WIS
{
	partial class GSSession
	{

		class SessionPacketHandler
		{

			#region handler_facility


			GSSession FSession;

			public delegate void PacketHandler(PacketStream packet);

			Dictionary<UInt32, PacketHandler> FHandlers;



			public SessionPacketHandler(GSSession session)
			{

				FSession = session;


				FHandlers = new Dictionary<UInt32, PacketHandler>();


				RegisterHandlers();

			}


			public bool RegisterHandler(UInt32 id, PacketHandler handler)
			{

				if (true == FHandlers.ContainsKey(id))
				{

					return false;

				}


				FHandlers[id] = handler;


				return true;

			}


			void OnUnhandledPacket(UInt32 id, UInt32 bytes)
			{

				Console.WriteLine("Unhandled packet[{0},{1}]", id, bytes);

			}
			public void OnPacket(byte[] data, int bytes)
			{

				PacketStream packet = new PacketStream(data, 0, bytes);


				UInt32 packetBytes = packet.ReadUInt32();

				UInt32 id = packet.ReadUInt32();


				if (FHandlers.ContainsKey(id) == false)
				{

					OnUnhandledPacket(id, packetBytes);

					return;

				}


				PacketHandler handler = FHandlers[id];


				if (handler != null)
				{

					handler(packet);

				}

			}


			#endregion



			void RegisterHandlers()
			{

				RegisterHandler(Packet.GS_2_WIS_USE_ROOKIE_CARD, OnRookieCard);

			}


			#region packet_handlers


			void OnKeepAlive(PacketStream packet)
			{

			}

			class RookieCardContext
			{
				public UInt32 playerId { get; set; }
				public string charName { get; set; }
			};

			void OnRookieCard(PacketStream packet)
			{
				UInt32 playerId = packet.ReadUInt32();

				string code = packet.ReadString();

				string charName = packet.ReadString();


				RookieCard.RookieCardSoapClient client = new RookieCard.RookieCardSoapClient();

				client.UseCardCompleted += new EventHandler<WIS.RookieCard.UseCardCompletedEventArgs>(client_UseCardCompleted);

				RookieCardContext context = new RookieCardContext();
				context.playerId = playerId;
				context.charName = charName;

				client.UseCardAsync(code, -1, -1, context);
			}


			void client_UseCardCompleted(object sender, RookieCard.UseCardCompletedEventArgs e)
			{

				PacketStream packet = new PacketStream();

				RookieCardContext context = (RookieCardContext)e.UserState;

				packet.WriteUInt32(0);

				packet.WriteUInt32(Packet.WIS_2_GS_USE_ROOKIE_CARD_RESULT);

				packet.WriteUInt32(context.playerId);

				packet.WriteByte((byte)e.Result);

				packet.WriteUInt32(e.itemTemplate);

				packet.WriteString(context.charName);

				uint len = packet.GetLength();

				packet.Seek(0);

				packet.WriteUInt32(len);


				FSession.SendPacket(packet);

			}


			#endregion

		};
	}
}
