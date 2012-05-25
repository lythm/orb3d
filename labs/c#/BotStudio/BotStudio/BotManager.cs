using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace BotStudio
{
	namespace BotEngine
	{
		public class BotManager
		{
			private BotDescriptor FBotDesc;
			private List<Bot>			FBotList;

			public BotDescriptor BotDesc
			{
				get
				{
					return FBotDesc;
				}
			}

			public BotManager(BotDescriptor BotDesc)
			{
				FBotDesc = BotDesc;
			}
			public void EmmitBotCommand(BotCommand command)
			{
				for (int i = 0; i < FBotList.Count; ++i)
				{
					FBotList[i].EmmitBotCommand(command);
				}
			}
			public bool StartBots()
			{
				FBotList = new List<Bot>(FBotDesc.Count);
				for (int i = 0; i < FBotDesc.Count; ++i)
				{
					Bot bot = new Bot(this, FBotDesc, i);
					FBotList.Add(bot);
					bot.Start();
				}


				AppContext.WriteLog("Bot["+FBotDesc.Name+"] started.");
				FBotDesc.Running = true;

				return true;
			}
			
			public void StopBots()
			{
				foreach(Bot bot in FBotList)
				{
					bot.Stop();
				}
				FBotList.Clear();

				AppContext.WriteLog("Bot[" + FBotDesc.Name + "] stopped.");

				FBotDesc.Running = false;
			}

			public string Script 
			{
				get
				{
					return FBotDesc.Script;
				}
			}
			public int BotCount
			{
				get
				{
					return FBotList.Count;
				}
			}
		}
	}
}