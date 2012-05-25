using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;
namespace BotStudio
{
	public partial class OutputForm : DockContent
	{
		public OutputForm()
		{
			InitializeComponent();
		}
		
		public void WriteLog(string log)
		{
		
			if (this.InvokeRequired)
			{
				MethodInvoker me = delegate { OutputString(log);};
				
				this.Invoke(me);

			}
			else
			{
				OutputString(log);
			}
		}

		private void OutputString(string log)
		{
			FLogTextBox.AppendText(log + "\r\n");


			FLogTextBox.ScrollToCaret();
			Refresh();


		}

		private void clearToolStripMenuItem_Click(object sender, EventArgs e)
		{
			FLogTextBox.Clear();
		}
	}
}
