using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.IO;



namespace BotStudio
{
	static class Program
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main()
		{
			if(false == AppContext.Initialize())
			{
				MessageBox.Show("Failed to initialize app");
				return;
			}

			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);
			Application.Run(new MainForm());

			AppContext.Release();
		}


		static void Test()
		{
			MemoryStream stream = new MemoryStream(1024);

			//stream.
			

		}
	}
}
