using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;

namespace BotStudio
{
	namespace BotEngine
	{
		public class BotDescriptor
		{
			public bool Running { get; set; }

			public List<BotCommand> BotCommands { get; set; }
			public int FCount = 1;
			public IPEndPoint Host { get; set; }
			public string Script { get; set; }
			public string Name { get; set; }
			public bool Silenced{get;set;}
			public int Count
			{
				get
				{
					return FCount;
				}
				set
				{
					FCount = value;
					if (FCount <= 0)
					{
						FCount = 1;
					}
				}
			}
			public BotDescriptor()
			{
				Script = "";
				Name = "No Name";
				Silenced = false;
				FCount = 1;

				IPAddress ip_addr = IPAddress.Parse("192.168.0.2");

				Host = new IPEndPoint(ip_addr, 9118);

				BotCommands = new List<BotCommand>();

				Running = false;

			}
		}
	}
}