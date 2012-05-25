using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;

namespace BotStudio
{
	public partial class NewBotDlg : Form
	{
		public int Count { get; set; }
		public BotEngine.BotDescriptor BotDesc{ get; set; }

		public NewBotDlg(string filePath)
		{
			InitializeComponent();

			BotDesc = new BotStudio.BotEngine.BotDescriptor();
			BotDesc.Script = filePath;
			BotDesc.Name = "Bot("+ filePath + ")";

			nameBox.Text = BotDesc.Name;

		}

		private void NewBotDlg_Load(object sender, EventArgs e)
		{
			silencedBox.Checked = false;

			if (Count <= 0)
			{
				Count = 1;
			}
			countBox.Value = Count;
			Text = BotDesc.Script;

			hostAddrBox.Text = "192.168.0.2";
		}

		private void NewBotDlg_FormClosed(object sender, FormClosedEventArgs e)
		{
		}

		private void NewBotDlg_FormClosing(object sender, FormClosingEventArgs e)
		{
		}

		private void OKButton_Click(object sender, EventArgs e)
		{
			DialogResult = DialogResult.OK;

			BotDesc.Name = nameBox.Text;

			if (BotDesc.Name.Length == 0)
			{
				BotDesc.Name = "No Name";
			}

			BotDesc.Silenced = silencedBox.Checked;
			BotDesc.Count = (int)countBox.Value;

			try
			{
				IPAddress ip_addr = IPAddress.Parse(hostAddrBox.Text);
				BotDesc.Host = new IPEndPoint(ip_addr, (int)portBox.Value);
			}
			catch(Exception ip_e)
			{
				MessageBox.Show(ip_e.Message);
				AppContext.WriteLog(ip_e.Message);
				DialogResult = DialogResult.None;
				return;
			}

		}

		private void CancelButton_Click(object sender, EventArgs e)
		{
			DialogResult = DialogResult.Cancel;
			//Close();
		}

		
	}
}
