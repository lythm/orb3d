using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Excel = Microsoft.Office.Interop.Excel;
using Office = Microsoft.Office.Core;
using Microsoft.Office.Tools.Excel;
using System.Xml;
using System.Windows.Forms;
using System.IO;

namespace DT_Excel_2007
{
	static class DT_Dialog
	{
		public static bool Import(Excel.Worksheet sheet, string file)
		{
			FileStream fs = File.Open(file, FileMode.Open);

			BinaryReader br = new BinaryReader(fs);

			fs.Close();

			return true;
		}

		public static bool Export(Excel.Worksheet sheet, string file)
		{
			return true;
		}
		public static void Check(Excel.Worksheet sheet)
		{
			Excel.Worksheet sh = Utils.CreateSheet();

			sh.Cells[1, 1] = "尚未实现敬请期待";
		}
	}
}
