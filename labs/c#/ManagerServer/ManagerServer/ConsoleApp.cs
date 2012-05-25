using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Threading;
namespace ManagerServer
{
    class ConsoleApp
    {
        public bool Run()
        {
            int workers, minio;
            ThreadPool.GetMinThreads(out workers, out minio);

            workers = Environment.ProcessorCount * 2;

            ThreadPool.SetMaxThreads(workers, minio);

            
            for (int i = 0; i < 1000; ++i)
            {
                ThreadPool.QueueUserWorkItem(Proc, i);
            }

            WaitForConsoleExit();
			 
            return true;
        }
        public static void Proc(Object state)
        {
            int i = (int)state;
           // Console.WriteLine("working {0}", i);

            ///Thread.Sleep(2000);
            Console.WriteLine("done  {0}", i);


        }
        public void WaitForConsoleExit()
        {
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.CreateNoWindow = false;
            startInfo.UseShellExecute = false;
            startInfo.FileName = "cmd.exe";
            startInfo.Arguments = "/c pause";

            Process p = Process.Start(startInfo);
            p.WaitForExit();
        }
    }
}
