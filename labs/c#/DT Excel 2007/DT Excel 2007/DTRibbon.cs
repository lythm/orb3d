using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Office.Tools.Ribbon;
using System.Windows.Forms;

using Excel = Microsoft.Office.Interop.Excel;
using Office = Microsoft.Office.Core;
using Microsoft.Office.Tools.Excel;


namespace DT_Excel_2007
{
    public partial class DTRibbon
    {
        private void DTRibbon_Load(object sender, RibbonUIEventArgs e)
        {
        }
        private void setupButton_Click(object sender, RibbonControlEventArgs e)
        {
            SetupForm sf = new SetupForm();

            if (sf.ShowDialog() != System.Windows.Forms.DialogResult.OK)
                return;
        }
        private void stringImportButton_Click(object sender, RibbonControlEventArgs e)
        {
			OpenFileDialog od = new OpenFileDialog();

            od.Filter = "String Table (*.xml)|*.xml|All Files (*.*)|*.*";

            od.FilterIndex = 0;
			od.Title = "导入字符串表";
            if (od.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            string file = od.FileName;

			Excel.Worksheet sh = Utils.CreateSheet();

			if (false == DT_String.Import(sh, file))
			{
				Utils.ShowError("导入失败");

				return;
			}

			MessageBox.Show("导入完成", "导入", MessageBoxButtons.OK, MessageBoxIcon.Information);

        }

		private void stringExportButton_Click(object sender, RibbonControlEventArgs e)
		{
			SaveFileDialog od = new SaveFileDialog();

			od.Filter = "String Table (*.xml)|*.xml|All Files (*.*)|*.*";

			od.FilterIndex = 0;
			od.Title = "导出字符串表";
			if (od.ShowDialog() != DialogResult.OK)
			{
				return;
			}

			string file = od.FileName;

			Excel.Worksheet activeSH = Utils.ActiveSheet();

			DT_String.Check(activeSH);

			if (MessageBox.Show("继续么", "是否继续导出", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No)
			{
				return;
			}

			if (false == DT_String.Export(activeSH, file))
			{
				Utils.ShowError("导出失败");
				return;
			}

			MessageBox.Show("导出完成", "导出", MessageBoxButtons.OK, MessageBoxIcon.Information);
		}

		private void checkStringButton_Click(object sender, RibbonControlEventArgs e)
		{
			DT_String.Check(Utils.ActiveSheet());
		}

		private void exportHSButton_Click(object sender, RibbonControlEventArgs e)
		{

			SaveFileDialog od = new SaveFileDialog();

			od.Filter = "String Table (*.dat)|*.dat|All Files (*.*)|*.*";

			od.FilterIndex = 0;
			od.Title = "导出HyperString表";
			if (od.ShowDialog() != DialogResult.OK)
			{
				return;
			}

			string file = od.FileName;

			Excel.Worksheet activeSH = Utils.ActiveSheet();

			DT_HyperString.Check(activeSH);

			if (MessageBox.Show("继续么", "是否继续导出", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No)
			{
				return;
			}

			try
			{
				DT_HyperString.Export(activeSH, file);
			}
			catch(Exception _e)
			{
				Utils.ShowError(_e.Message + "\r\n" + "导出失败");
			}

			MessageBox.Show("导出完成", "导出", MessageBoxButtons.OK, MessageBoxIcon.Information);
		}

		private void importHSButton_Click(object sender, RibbonControlEventArgs e)
		{
			OpenFileDialog od = new OpenFileDialog();

			od.Filter = "HyperString Table (*.dat)|*.dat|All Files (*.*)|*.*";

			od.FilterIndex = 0;
			od.Title = "导入HyperString表";
			if (od.ShowDialog() != DialogResult.OK)
			{
				return;
			}

			string file = od.FileName;

			Excel.Worksheet sh = Utils.CreateSheet();

			if (false == DT_HyperString.Import(sh, file))
			{
				Utils.ShowError("导入失败");

				return;
			}

			MessageBox.Show("导入完成", "导入", MessageBoxButtons.OK, MessageBoxIcon.Information);
		}

		private void checkHSButton_Click(object sender, RibbonControlEventArgs e)
		{
			DT_HyperString.Check(Utils.ActiveSheet());
		}

		private void hsItemLinkButton_Click(object sender, RibbonControlEventArgs e)
		{
			DT_HyperString.AddTemplate_Item();
		}

		private void hsMobLinkButton_Click(object sender, RibbonControlEventArgs e)
		{
			DT_HyperString.AddTemplate_Mob();
		}

		private void hsWPLinkButton_Click(object sender, RibbonControlEventArgs e)
		{
			DT_HyperString.AddTemplate_Waypoint();
		}

		private void dlgCheckButton_Click(object sender, RibbonControlEventArgs e)
		{

		}

		private void hsPrevButton_Click(object sender, RibbonControlEventArgs e)
		{
			DT_HyperString.Preview();
		}

		private void reloadButton_Click(object sender, RibbonControlEventArgs e)
		{
			Utils.ReloadAssets();
		}

		private void maplinkButton_Click(object sender, RibbonControlEventArgs e)
		{
			DT_HyperString.AddTemplate_Map();
		}

		private void charnameButton_Click(object sender, RibbonControlEventArgs e)
		{
			DT_HyperString.AddTemplate_CharName();
		}

		private void charproLinkButton_Click(object sender, RibbonControlEventArgs e)
		{
			DT_HyperString.AddTemplate_CharPro();
		}

		private void newlineButton_Click(object sender, RibbonControlEventArgs e)
		{
			DT_HyperString.AddTemplate_Newline();
		}

		private void correctButton_Click(object sender, RibbonControlEventArgs e)
		{
			DT_HyperString.Correct();
		}
    }
}
