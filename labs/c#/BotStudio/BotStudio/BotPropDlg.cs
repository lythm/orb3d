using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Configuration;
namespace BotStudio
{
	public partial class BotPropDlg : Form
	{
		public int Count { get; set; }
		public BotEngine.BotDescriptor BotDesc{ get; set; }
		private PropertyPack.PropertyTable FPropTable;

		public BotPropDlg(string filePath)
		{
			InitializeComponent();

			BotDesc = new BotStudio.BotEngine.BotDescriptor();
			BotDesc.Script = filePath;
			BotDesc.Name = ConfigurationManager.AppSettings["DefaultBotName"];
			BotDesc.Count = 1;
			BotDesc.Silenced = false;
			BotDesc.Host.Address = IPAddress.Parse(ConfigurationManager.AppSettings["DefaultHostAddress"]);
			BotDesc.Host.Port = Convert.ToInt32(ConfigurationManager.AppSettings["DefaultHostPort"]);

			
			
		}

		public BotPropDlg(BotEngine.BotDescriptor botDesc)
		{
			InitializeComponent();

			BotDesc = botDesc;

		}

		private void NewBotDlg_Load(object sender, EventArgs e)
		{
			Text = BotDesc.Script;
			
			FPropTable = new BotStudio.PropertyPack.PropertyTable();

			BotStudio.PropertyPack.PropertySpec prop = new BotStudio.PropertyPack.PropertySpec("Name", typeof(string));
			FPropTable.Properties.Add(prop);
			FPropTable["Name"] = BotDesc.Name;

			prop = new BotStudio.PropertyPack.PropertySpec("Count", typeof(int));
			FPropTable.Properties.Add(prop);
			FPropTable["Count"] = BotDesc.Count;

			prop = new BotStudio.PropertyPack.PropertySpec("Silence Mode", typeof(bool));
			FPropTable.Properties.Add(prop);
			FPropTable["Silence Mode"] = BotDesc.Silenced;


			prop = new BotStudio.PropertyPack.PropertySpec("HostAddress", typeof(IPAddress));

			prop.Attributes = new Attribute[] { new EditorAttribute(typeof(PropertyGridIPAddressInput), typeof(System.Drawing.Design.UITypeEditor)) };
			FPropTable.Properties.Add(prop);
			FPropTable["HostAddress"] = BotDesc.Host.Address;


			prop = new BotStudio.PropertyPack.PropertySpec("HostPort", typeof(int));
			FPropTable.Properties.Add(prop);
			FPropTable["HostPort"] = BotDesc.Host.Port;


			prop = new BotStudio.PropertyPack.PropertySpec("Script", typeof(string));
			prop.Attributes = new Attribute[]{new ReadOnlyAttribute(true)};
			FPropTable.Properties.Add(prop);
			FPropTable["Script"] = BotDesc.Script;

			propGrid.SelectedObject = FPropTable;
		}

		private void NewBotDlg_FormClosed(object sender, FormClosedEventArgs e)
		{
		}

		private void NewBotDlg_FormClosing(object sender, FormClosingEventArgs e)
		{
		}

		private void OKButton_Click(object sender, EventArgs e)
		{
			if (BotDesc.Running)
			{
				if (MessageBox.Show("To apply the modification, bots must be restarted.", "warning", MessageBoxButtons.OKCancel) != DialogResult.OK)
				{
					return;
				}
			}

			DialogResult = DialogResult.OK;

			BotDesc.Name = (string)FPropTable["Name"];

			BotDesc.BotCommands.Clear();

			if (BotDesc.Name.Length == 0)
			{
				BotDesc.Name = "No Name";
			}

			BotDesc.Silenced = (bool)FPropTable["Silence Mode"];
			BotDesc.Count = (int)FPropTable["Count"];

			try
			{
				IPAddress ip_addr = (IPAddress)FPropTable["HostAddress"];
				BotDesc.Host = new IPEndPoint(ip_addr, (int)FPropTable["HostPort"]);

				LuaInterface.Lua lua = new LuaInterface.Lua();

				lua.DoFile(BotDesc.Script);

				LuaInterface.LuaTable bot_cmds = lua.GetTable("BotCommandList");

				if (bot_cmds != null)
				{
					foreach (object cmd_name in bot_cmds.Keys)
					{
						BotEngine.BotCommand cmd = new BotStudio.BotEngine.BotCommand(BotDesc, (string)cmd_name);

						BotDesc.BotCommands.Add(cmd);


						LuaInterface.LuaTable param_table = (LuaInterface.LuaTable)bot_cmds[(string)cmd_name];
						if (param_table == null)
						{
							continue;
						}


						foreach (object param in param_table.Values)
						{
							cmd.Parameters.Add(new BotEngine.BotCommand.Parameter((string)param, ""));
						}
					}
				}
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
		}
	}
}
