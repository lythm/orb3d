using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BotStudio
{
	public class BotList
	{
		List<BotEngine.BotDescriptor> FBots = new List<BotStudio.BotEngine.BotDescriptor>();

		public delegate void Event_OnListChanged();

		public Event_OnListChanged OnListChanged{get;set;}

		public List<BotEngine.BotDescriptor> Bots
		{
			get
			{
				return FBots;
			}
		}

		public BotList()
		{
			
		}
		
		public void AddBot(BotEngine.BotDescriptor bot)
		{
			FBots.Add(bot);
			Emmit_ListChanged();
		}
		public void Clear()
		{
			FBots.Clear();
			Emmit_ListChanged();
		}
		public void RemoveBot(BotEngine.BotDescriptor bot)
		{
			FBots.Remove(bot);
			Emmit_ListChanged();
		}
		public void RemoveBot(List<BotEngine.BotDescriptor> bots)
		{
			foreach (BotEngine.BotDescriptor bot in bots)
			{
				FBots.Remove(bot);
			}

			Emmit_ListChanged();
		}

		public int GetBotCount()
		{
			return FBots.Count;
		}

		public void Emmit_ListChanged()
		{
			if (OnListChanged != null)
			{
				OnListChanged();
			}
		}
	}
}
