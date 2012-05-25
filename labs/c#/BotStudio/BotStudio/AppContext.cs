using System;
using System.Collections.Generic;

using System.Text;
using System.Windows.Forms;
using System.Threading;
using LuaInterface;
using System.Drawing;

using System.Diagnostics;

namespace BotStudio
{
	class AppContext
	{
		static public MainForm GetMainForm()
		{
			MainForm main = (MainForm)Application.OpenForms[0];
			return main;
		}
				
		static public void WriteLog(string log)
		{
			MainForm main = (MainForm)Application.OpenForms[0];

			main.WriteLog(log);

			Debug.WriteLine(log);

		}
		static public bool Initialize()
		{
			FBotEngine = new BotStudio.BotEngine.BotEngine();
			
			ThreadPool.SetMinThreads(4, 4);
			ThreadPool.SetMaxThreads(8, 8);

			BotTplList = new BotTemplateList();
			BotList = new BotList();
			return true;
		}
		static public void Release()
		{
			FBotEngine = null;
		}

		static public BotEngine.BotEngine BotEngine
		{
			get
			{
				return FBotEngine;
			}
		}
		

		
		
		static private BotEngine.BotEngine FBotEngine;

		static public BotTemplateList BotTplList { get; set; }
		static public BotList BotList { get; set; }
	}
}
