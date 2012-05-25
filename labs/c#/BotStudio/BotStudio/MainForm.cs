using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using BotStudio.BotEngine;
using System.Net;
using WeifenLuo.WinFormsUI.Docking;
namespace BotStudio
{
	public partial class MainForm : Form
	{
		private OutputForm FOutputForm;


		public MainForm()
		{
			InitializeComponent();
		}
	
		public void WriteLog(string log)
		{
			FOutputForm.WriteLog(log);
		}
		private void MainForm_Load(object sender, EventArgs e)
		{
			FOutputForm = new OutputForm();
			FOutputForm.Show(DockPanel);
			
			WriteLog("Bot Studio Started.");


			BotTemplatesForm t = new BotTemplatesForm(AppContext.BotTplList);

			t.Show(DockPanel);


			BotListForm l = new BotListForm();
			l.Show(DockPanel);

			AppContext.BotTplList.Update();
		}

		private void botTemplateListToolStripMenuItem_Click(object sender, EventArgs e)
		{
			foreach (DockContent c in DockPanel.Contents)
			{
				if (c is BotTemplatesForm)
				{
					c.Show(DockPanel);
					return;
				}
			}

			BotTemplatesForm t = new BotTemplatesForm(AppContext.BotTplList);

			t.Show(DockPanel);
		}

		private void botListToolStripMenuItem_Click(object sender, EventArgs e)
		{
			foreach (DockContent c in DockPanel.Contents)
			{
				if (c is BotListForm)
				{
					c.Show(DockPanel);
					return;
				}
			}

			BotListForm t = new BotListForm();
			t.Show(DockPanel);
		}

		private void outputWindowToolStripMenuItem_Click(object sender, EventArgs e)
		{
			FOutputForm.Show(DockPanel);
		}

		private void ConfigMenuItem_Click(object sender, EventArgs e)
		{
			ConfigForm form = new ConfigForm();
			form.ShowDialog(this);
		}

	}
}
