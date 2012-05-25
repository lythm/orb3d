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
	public partial class BotListForm : DockContent
	{
		public BotListForm()
		{
			InitializeComponent();
		}

		private void OnListChanged()
		{
			UpdateFromList();
		}
		private void BotListForm_Load(object sender, EventArgs e)
		{
			UpdateFromList();
			AppContext.BotList.OnListChanged += OnListChanged;
		}
		private void UpdateFromList()
		{
			BotList.Items.Clear();
			foreach (BotEngine.BotDescriptor bot in AppContext.BotList.Bots)
			{
				AddBotTemplate(bot);
			}
		}
		private void AddBotTemplate(BotEngine.BotDescriptor bot)
		{
			ListViewItem item = new ListViewItem();
			item.Text = bot.Name;

			item.SubItems.Add(bot.Count.ToString());
			item.SubItems.Add(bot.Silenced.ToString());
			item.SubItems.Add(bot.Host.ToString());
			item.SubItems.Add(bot.Running ? "running" : "stopped");
			item.SubItems.Add(bot.Script);
			item.Tag = bot;

			BotList.Items.Add(item);
		}
		private void BotList_DragDrop(object sender, DragEventArgs e)
		{
			string file = (string)e.Data.GetData(typeof(string));

			BotPropDlg dlg = new BotPropDlg(file);
			dlg.ShowDialog(this.Parent);

			if (dlg.DialogResult == DialogResult.OK)
			{
				AppContext.BotList.AddBot(dlg.BotDesc);
			}
		}

		private void BostList_DragEnter(object sender, DragEventArgs e)
		{
			if (e.Data.GetDataPresent(typeof(string)))
				e.Effect = DragDropEffects.Copy;
			else
				e.Effect = DragDropEffects.None;
		}

		private void refreshListToolStripMenuItem_Click(object sender, EventArgs e)
		{
			UpdateFromList();
		}

		private void OnBotCommand_Click(object sender, EventArgs e)
		{
			ToolStripMenuItem item = sender as ToolStripMenuItem;

			if(item == null)
				return;

			BotEngine.BotCommand cmd = (BotEngine.BotCommand)item.Tag;

			if (cmd.Parameters.Count != 0)
			{
				BotCommandForm bf = new BotCommandForm(cmd);

				if (bf.ShowDialog(this) != DialogResult.OK)
					return;
			}

			AppContext.BotEngine.EmmitBotCommand(cmd);
		}
		private void runToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (BotList.SelectedItems.Count == 0)
			{
				return;
			}

			foreach (ListViewItem item in BotList.SelectedItems)
			{
				BotEngine.BotDescriptor bot = (BotEngine.BotDescriptor)item.Tag;
				if (bot == null)
					continue;

				if (false == AppContext.BotEngine.Run(bot))
				{
					AppContext.WriteLog("Failed to start bot " + bot.Name);
				}
			}

			UpdateFromList();
		}

		private void botListContextMenu_Opening(object sender, CancelEventArgs e)
		{
			restartMenuItem.Enabled = false;
			botCommand.DropDown.Items.Clear();
			botCommand.Enabled = false;
			runToolStripMenuItem.Enabled = false;
			stopToolStripMenuItem.Enabled = false;
			removeToolStripMenuItem.Enabled = false;
			modifyMenuItem.Enabled = false;

			if (BotList.SelectedItems.Count != 0)
			{
				removeToolStripMenuItem.Enabled = true;
				modifyMenuItem.Enabled = true;

				BotEngine.BotDescriptor bot = (BotEngine.BotDescriptor)BotList.SelectedItems[0].Tag;

				if (bot.Running)
				{
					stopToolStripMenuItem.Enabled = true;
					botCommand.Enabled = true;
					restartMenuItem.Enabled = true;
				}
				else
				{
					runToolStripMenuItem.Enabled = true;
				}


				if (bot.BotCommands.Count == 0)
				{
					ToolStripMenuItem item = new ToolStripMenuItem("No Command");
					botCommand.DropDown.Items.Add(item);
				}
				else
				{
					foreach (BotEngine.BotCommand cmd in bot.BotCommands)
					{
						ToolStripMenuItem item = new ToolStripMenuItem();
						item.Name = cmd.CommandName;
						item.Text = cmd.CommandName;
						item.Tag = cmd;
						item.Click += OnBotCommand_Click;

						botCommand.DropDown.Items.Add(item);
					}
				}

			}
		}

		private void removeToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (BotList.SelectedItems.Count == 0)
				return;

			List<BotEngine.BotDescriptor> removeList = new List<BotStudio.BotEngine.BotDescriptor>();
			foreach (ListViewItem item in BotList.SelectedItems)
			{
				BotEngine.BotDescriptor bot = (BotEngine.BotDescriptor)item.Tag;

				AppContext.BotEngine.Remove(bot);
				removeList.Add(bot);
			}

			AppContext.BotList.RemoveBot(removeList);
		}

		private void stopToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (BotList.SelectedItems.Count == 0)
				return;

			foreach (ListViewItem item in BotList.SelectedItems)
			{
				BotEngine.BotDescriptor bot = (BotEngine.BotDescriptor)item.Tag;

				AppContext.BotEngine.Stop(bot);
			}

			UpdateFromList();
		}

		private void modifyMenuItem_Click(object sender, EventArgs e)
		{
			if (BotList.SelectedItems.Count == 0)
				return;

			BotEngine.BotDescriptor bot = (BotEngine.BotDescriptor)BotList.SelectedItems[0].Tag;

			BotPropDlg dlg = new BotPropDlg(bot);
			if (dlg.ShowDialog(this.Parent) != DialogResult.OK)
			{
				return;
			}

			if (bot.Running)
			{

				if (false == AppContext.BotEngine.Run(bot))
				{
					AppContext.WriteLog("Failed to restart bot " + bot.Name);
				}
			}
			
			UpdateFromList();

		}

		private void restartMenuItem_Click(object sender, EventArgs e)
		{
			if (BotList.SelectedItems.Count == 0)
			{
				return;
			}

			foreach (ListViewItem item in BotList.SelectedItems)
			{
				BotEngine.BotDescriptor bot = (BotEngine.BotDescriptor)item.Tag;
				if (bot == null)
					continue;

				if (false == AppContext.BotEngine.Run(bot))
				{
					AppContext.WriteLog("Failed to restart bot " + bot.Name);
				}
			}

			UpdateFromList();
		}

		private void BotList_ItemActivate(object sender, EventArgs e)
		{
			modifyMenuItem_Click(sender, e);
		}
	}
}
