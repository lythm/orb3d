using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace BotStudio
{
	public partial class BotCommandForm : Form
	{
		BotEngine.BotCommand FCommand;

		PropertyPack.PropertyTable FPropertyTable;

		public BotCommandForm(BotEngine.BotCommand cmd)
		{
			InitializeComponent();
			FCommand = cmd;
			
			FPropertyTable = new BotStudio.PropertyPack.PropertyTable();


			foreach(BotEngine.BotCommand.Parameter param in cmd.Parameters)
			{
				FPropertyTable.Properties.Add(new BotStudio.PropertyPack.PropertySpec(param.Name, typeof(string)));
			}

			commandPropList.SelectedObject = FPropertyTable;

		}

		private void okButton_Click(object sender, EventArgs e)
		{
			DialogResult = DialogResult.OK;

			for (int i = 0; i < FCommand.Parameters.Count; ++i)
			{
				FCommand.Parameters[i].Value = (string)FPropertyTable[FCommand.Parameters[i].Name];
			}
		}

		private void cancelButton_Click(object sender, EventArgs e)
		{
			DialogResult = DialogResult.Cancel;
		}
	}
}
