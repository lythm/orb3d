using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BotStudio
{
	namespace BotEngine
	{
		public class BotEngine
		{
			List<BotManager> FBotManagers;

			public BotEngine()
			{
				FBotManagers = new List<BotManager>();
			}

			BotManager FindBotManager(BotDescriptor bot)
			{
				return FBotManagers.Find((manager) => { return manager.BotDesc == bot;});
			}

			public void EmmitBotCommand(BotCommand cmd)
			{
				try
				{
					BotManager manager = FindBotManager(cmd.BotDesc);

					if (manager == null)
						return;

					manager.EmmitBotCommand(cmd);

				}
				catch (Exception e)
				{
					AppContext.WriteLog(e.Message);
					return;
				}
			}

			public bool Run(BotDescriptor botDesc)
			{
				GC.Collect();
				GC.WaitForPendingFinalizers();

				try
				{
					BotManager manager = FindBotManager(botDesc);

					if (manager != null)
					{
						manager.StopBots();
						
						manager.StartBots();
						return true;
					}

					BotManager botManager = new BotManager(botDesc);

					botManager.StartBots();

					FBotManagers.Add(botManager);
				}
				catch (Exception e)
				{
					AppContext.WriteLog(e.Message);
					return false;
				}
				return true;
			}
			public void Stop(BotDescriptor botDesc)
			{
				try
				{
					BotManager manager = FindBotManager(botDesc);
					
					if(manager != null)
					{
						manager.StopBots();
					}
					
				}
				catch (Exception e)
				{
					AppContext.WriteLog(e.Message);
				}

				GC.Collect();
				GC.WaitForPendingFinalizers();
			}
			public void Remove(BotDescriptor botDesc)
			{
				try
				{

					BotManager managerToRemove = FindBotManager(botDesc);

					if (managerToRemove != null)
					{
						managerToRemove.StopBots();
						FBotManagers.Remove(managerToRemove);
					}
				}
				catch (Exception e)
				{
					AppContext.WriteLog(e.Message);
				}

				GC.Collect();
				GC.WaitForPendingFinalizers();
			}
		}
	}
}
