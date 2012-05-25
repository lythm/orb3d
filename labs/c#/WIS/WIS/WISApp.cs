using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Diagnostics;
namespace WIS
{
	class WISApp
	{
		GSHost FGSHost;

		public WISApp()
		{

		}


		public bool Initialize()
		{

			if (EventLog.SourceExists("WIS") == false)
			{
				EventLog.CreateEventSource("WIS", "Elementia");
			}
			

			FGSHost = new GSHost();

			if (false == FGSHost.Open())
			{

				Console.WriteLine("Failed to open GSHost.");

				return false;

			}

			EventLog.WriteEntry("WIS", "WIS Started", EventLogEntryType.Information);

			Console.WriteLine("WIS Started.");

			return true;
		}


		public void Run()
		{
			string cmdline = "";


			while(true)
			{

				cmdline = Console.ReadLine();


				if (OnCommandLine(cmdline) == false)
				{

					break;

				}


			} 

		}


		public void Release()
		{

			FGSHost.Close();

			EventLog.WriteEntry("WIS", "WIS Stopped", EventLogEntryType.Information);

			Console.WriteLine("WIS Stopped.");

		}


		bool OnCommandLine(string cmdline)
		{

			switch (cmdline)
			{

				case "quit":

					return false;

				default:

					break;

			}

			return true;
		}
	}
}
