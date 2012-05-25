using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Configuration;
using System.Net;

namespace BotStudio
{
	public partial class ConfigForm : Form
	{
		PropertyPack.PropertyTable FPropTable;

		string FCurrentPath = "";
		
		public ConfigForm()
		{
			InitializeComponent();
		}

		private void ConfigForm_Load(object sender, EventArgs e)
		{
			FCurrentPath  = Directory.GetCurrentDirectory();

			FPropTable = new BotStudio.PropertyPack.PropertyTable();


			BotStudio.PropertyPack.PropertySpec prop = new BotStudio.PropertyPack.PropertySpec("BotRoot", typeof(string));
			FPropTable.Properties.Add(prop);
			FPropTable["BotRoot"] = ConfigurationManager.AppSettings["BotRoot"];

			prop = new BotStudio.PropertyPack.PropertySpec("BotEditor", typeof(string));
			prop.Attributes = new Attribute[] { new EditorAttribute(typeof(PropertyGridFilePicker), typeof(System.Drawing.Design.UITypeEditor)) };
			FPropTable.Properties.Add(prop);
			FPropTable["BotEditor"] = ConfigurationManager.AppSettings["BotEditor"];

			prop = new BotStudio.PropertyPack.PropertySpec("DefaultHostAddress", typeof(IPAddress));
			prop.Attributes = new Attribute[] { new EditorAttribute(typeof(PropertyGridIPAddressInput), typeof(System.Drawing.Design.UITypeEditor)) };
			FPropTable.Properties.Add(prop);
			FPropTable["DefaultHostAddress"] = IPAddress.Parse(ConfigurationManager.AppSettings["DefaultHostAddress"]);


			prop = new BotStudio.PropertyPack.PropertySpec("DefaultHostPort", typeof(int));
			FPropTable.Properties.Add(prop);
			FPropTable["DefaultHostPort"] = ConfigurationManager.AppSettings["DefaultHostPort"];

			prop = new BotStudio.PropertyPack.PropertySpec("DefaultBotName", typeof(string));
			FPropTable.Properties.Add(prop);
			FPropTable["DefaultBotName"] = ConfigurationManager.AppSettings["DefaultBotName"];

			configPropGrid.SelectedObject = FPropTable;
		}

		private void ConfigForm_FormClosed(object sender, FormClosedEventArgs e)
		{
			Directory.SetCurrentDirectory(FCurrentPath);
		}

		private void okButton_Click(object sender, EventArgs e)
		{
			DialogResult = DialogResult.OK;

			Configuration config = ConfigurationManager.OpenExeConfiguration(System.Configuration.ConfigurationUserLevel.None);

			foreach (PropertyPack.PropertySpec p in FPropTable.Properties)
			{
				config.AppSettings.Settings[p.Name].Value = FPropTable[p.Name].ToString();
				ConfigurationManager.AppSettings[p.Name] = FPropTable[p.Name].ToString();
			}
						
			config.Save();

			
		}

		private void cancelButton_Click(object sender, EventArgs e)
		{
			DialogResult = DialogResult.Cancel;
		}
	}
}
