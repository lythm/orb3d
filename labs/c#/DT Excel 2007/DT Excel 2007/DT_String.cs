using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Excel = Microsoft.Office.Interop.Excel;
using Office = Microsoft.Office.Core;
using Microsoft.Office.Tools.Excel;
using System.Xml;
using System.Windows.Forms;

namespace DT_Excel_2007
{
	static class DT_String
	{
		public static bool Check(Excel.Worksheet sheet)
		{
			Excel.Range ur = sheet.UsedRange;

			Dictionary<string, int> checkMap = new Dictionary<string, int>();


			List<string> idList = new List<string>();
			List<string> vList = new List<string>();

			for (int rCnt = 1; rCnt <= ur.Rows.Count; rCnt++)
			{
				Excel.Range r1 = ur.Cells[rCnt, 1] as Excel.Range;
				Excel.Range r2 = ur.Cells[rCnt, 2] as Excel.Range;

				object id = r1.Value2;
				object v = r2.Value2;

				if (id == null || v == null)
				{
					idList.Add(sheet.Name + "!" + r1.Address);
					vList.Add(sheet.Name + "!" + r2.Address);

					continue;
				}

				int x = 0;
				if (int.TryParse(id.ToString(), out x) == false)
				{
					idList.Add(sheet.Name + "!" + r1.Address);
					vList.Add(sheet.Name + "!" + r2.Address);

					continue;
				}

				if (checkMap.ContainsKey(id.ToString()))
				{
					checkMap[id.ToString()] += 1;
				}
				else
				{
					checkMap.Add(id.ToString(), 1);
				}
			}

			Excel.Worksheet sh = Utils.CreateSheet();

			int irow = 1;

			if (checkMap.Keys.Count > 0)
			{
				sh.Cells[irow, 1] = "以下字符串id存在冲突";
				++irow;

				sh.Cells[irow, 1] = "id";
				sh.Cells[irow, 2] = "冲突次数";

				++irow;

				foreach (KeyValuePair<string, int> v in checkMap)
				{
					if (v.Value > 1)
					{
						sh.Cells[irow, 1] = v.Key;
						sh.Cells[irow, 2] = v.Value;
						++irow;
					}
				}
			}

			++irow;
			++irow;

			sh.Cells[irow, 1] = "以下字符串无效";

			++irow;

			sh.Cells[irow, 1] = "id";
			sh.Cells[irow, 2] = "内容";

			++irow;

			for (int i = 0; i < idList.Count; ++i)
			{
				Excel.Range r = sh.Cells[irow, 1] as Excel.Range;
				sh.Hyperlinks.Add(r, "", idList[i], Type.Missing, "=" + idList[i]);

				r = sh.Cells[irow, 2] as Excel.Range;

				sh.Hyperlinks.Add(r, "", vList[i], Type.Missing, "=" + vList[i]);

				++irow;
			}

			sh.Columns.HorizontalAlignment = Excel.XlHAlign.xlHAlignLeft;

			Utils.SetColoumWidth(sh, 1, 20);
			Utils.SetColoumWidth(sh, 2, 200);

			
			return true;
		}
		public static bool Import(Excel.Worksheet sheet, string file)
		{
			XmlDocument doc = new XmlDocument();

			doc.Load(file);

			XmlNode table = doc.SelectSingleNode("table");

			if (table == null)
				return false;

			int irow = 1;

			int max_text_len = 0;


			foreach (XmlNode n in table.ChildNodes)
			{

				XmlElement e = n as XmlElement;

				if (e == null)
				{
					if (n is XmlComment)
						continue;

					return false;
				}

				sheet.Cells[irow, 1] = e.Attributes["id"].Value;
				sheet.Cells[irow, 2] = e.InnerText;

				if (e.InnerText.Length > max_text_len)
				{
					max_text_len = e.InnerText.Length;
				}

				++irow;
			}

			sheet.UsedRange.Columns.HorizontalAlignment = Excel.XlHAlign.xlHAlignLeft;

			Utils.SetColoumWidth(sheet, 2, max_text_len);

			return true;
		}
		public static bool Export(Excel.Worksheet sheet, string file)
		{

			XmlDocument doc = new XmlDocument();

			XmlElement table = doc.CreateElement("table");


			Excel.Range ur = sheet.UsedRange;

			for (int rCnt = 1; rCnt <= ur.Rows.Count; rCnt++)
			{
				object id = ((ur.Cells[rCnt, 1] as Excel.Range).Value2);
				object v = ((ur.Cells[rCnt, 2] as Excel.Range).Value2);

				if (id == null)
				{
					continue;
				}

				XmlElement str = doc.CreateElement("string");

				str.SetAttribute("id", id.ToString());

				if (v == null)
				{
					str.InnerText = "";
				}
				else
				{
					str.InnerText = v.ToString();
				}

				table.AppendChild(str);

			}

			doc.AppendChild(table);
			doc.Save(file);

			return true;
		}
	}
}
