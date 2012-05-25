using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WIS
{
	class Program
	{

		static public WISApp App{get;set;}

		static void Main(string[] args)
		{
			Console.CancelKeyPress+= OnCancel;

			App = new WISApp();


			if (false == App.Initialize())
			{

				Console.WriteLine("Failed to init app.");


				return;

			}


			App.Run();

			App.Release();

		}

		static void OnCancel(Object sender, ConsoleCancelEventArgs e)
		{

			e.Cancel = true;

			Console.WriteLine("type quit to exit.");

		}
	}
}
