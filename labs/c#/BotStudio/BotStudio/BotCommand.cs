using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;

namespace BotStudio
{
	namespace BotEngine
	{
		public class BotCommand
		{
			public class Parameter
			{
				public Parameter(string name, string value)
				{
					Name = name;
					Value = value;
				}
				public string Name { get; set; }
				public string Value{get;set;}
			}

			public BotDescriptor BotDesc { get; set; }
			public string CommandName { get; set; }
			public List<Parameter> Parameters { get; set; }

			public BotCommand(BotDescriptor bot, string name)
			{
				BotDesc = bot;
				CommandName = name;
				Parameters = new List<Parameter>();
			}
		}
	}
}