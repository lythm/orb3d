using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Excel = Microsoft.Office.Interop.Excel;
using Office = Microsoft.Office.Core;
using Microsoft.Office.Tools.Excel;


namespace DT_Excel_2007
{
    public partial class SetupForm : Form
    {
        public SetupForm()
        {
            InitializeComponent();
        }

        private void SetupForm_Load(object sender, EventArgs e)
        {
			string assetRoot = Utils.GetCustomProp(Utils.ActiveBook(), "EDT_assets_root") as string;

			if (assetRoot != null)
			{
				assetsPathEdit.Text = assetRoot;
			}
        }

		private void OKButton_Click(object sender, EventArgs e)
		{
			if (assetsPathEdit.Text[assetsPathEdit.Text.Length - 1] != '/' || assetsPathEdit.Text[assetsPathEdit.Text.Length - 1] != '\\')
			{
				assetsPathEdit.Text += '/';
			}
		
			Utils.SetCustomProp(Utils.ActiveBook(), "EDT_assets_root", assetsPathEdit.Text);
			
			DialogResult = System.Windows.Forms.DialogResult.OK;
		}

		private void assetsBrowseButton_Click(object sender, EventArgs e)
		{
			FolderBrowserDialog fd = new FolderBrowserDialog();

			if (fd.ShowDialog() != System.Windows.Forms.DialogResult.OK)
				return;

			assetsPathEdit.Text = fd.SelectedPath;
		}
    }
}
