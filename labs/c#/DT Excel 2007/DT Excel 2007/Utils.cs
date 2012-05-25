using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Excel = Microsoft.Office.Interop.Excel;
using Office = Microsoft.Office.Core;
using Microsoft.Office.Tools.Excel;
using System.Xml;


namespace DT_Excel_2007
{
	public static class Utils
	{
		static Dictionary<int, string> FStringTable = null;

		public static string GetMapName(UInt32 map_id)
		{
			if (FStringTable == null)
			{
				return "";
			}

			int id = LuaUtil.GetMapNameId(map_id);

			if (id == -1)
			{
				return "";
			}

			if (FStringTable.ContainsKey(id) == false)
			{
				return "";
			}
			string name = FStringTable[id];

			return name;
		}
		public static string GetWaypointName(UInt32 wp_id)
		{
			if (FStringTable == null)
			{
				return "";
			}

			int id = LuaUtil.GetWaypointNameId(wp_id);

			if (id == -1)
			{
				return "";
			}

			if (FStringTable.ContainsKey(id) == false)
			{
				return "";
			}
			string name = FStringTable[id];

			return name;
		}
		public static string GetMobName(UInt32 mob_id)
		{
			if (FStringTable == null)
			{
				return "";
			}

			int id = LuaUtil.GetMobNameId(mob_id);

			if (id == -1)
			{
				return "";
			}

			if (FStringTable.ContainsKey(id) == false)
			{
				return "";
			}
			string name = FStringTable[id];

			return name;
		}
		public static string GetItemName(UInt32 item_id)
		{
			if (FStringTable == null)
			{
				return "";
			}

			int id = LuaUtil.GetItemNameId(item_id);

			if (id == -1)
			{
				return "";
			}

			if (FStringTable.ContainsKey(id) == false)
			{
				return "";
			}
			string name = FStringTable[id];

			return name;
		}

		public static void ReloadAssetsIfNot()
		{
			try
			{
				LuaUtil.ReloadIfNot();

				if (FStringTable == null)
				{
					ReloadStringTable();
				}
			}
			catch (Exception e)
			{
				Utils.ShowError(e + "\r\n" + "无法加载资源,请检查设置");
				FStringTable = null;
				LuaUtil.Clear();
			}

		}

		public static void ReloadAssets()
		{
			try
			{
				LuaUtil.Reload();

				ReloadStringTable();
			}
			catch (Exception e)
			{
				Utils.ShowError(e + "\r\n" + "无法加载资源,请检查设置");
				FStringTable = null;
				LuaUtil.Clear();
			}
		}
		public static bool ReloadStringTable()
		{
			FStringTable = new Dictionary<int, string>();

			XmlDocument doc = new XmlDocument();


			object val = Utils.GetCustomProp(Utils.ActiveBook(), "EDT_assets_root");

			string assets_root = "";
			if (val != null)
			{
				assets_root = val.ToString();
			}

			string file = assets_root + "strings/string_table.xml";

			doc.Load(file);

			XmlNode table = doc.SelectSingleNode("table");

			if (table == null)
				return false;

			foreach (XmlNode n in table.ChildNodes)
			{

				XmlElement e = n as XmlElement;

				if (e == null)
				{
					if (n is XmlComment)
						continue;

					return false;
				}

				int id = Convert.ToInt32(e.Attributes["id"].Value);
				string str = e.InnerText;

				FStringTable.Add(id, str);
			}

			return true;

		}

		public static Excel.Range SelectedRange()
		{
			return Globals.ThisAddIn.Application.Selection as Excel.Range;
		}
		public static void SetColoumWidth(Excel.Worksheet sheet, int col, int width)
		{
			(sheet.Columns[col] as Excel.Range).ColumnWidth = width;
		}
		public static Excel.Worksheet CreateSheet()
		{
			Excel.Workbook wb = Globals.ThisAddIn.Application.ActiveWorkbook;

			object last = wb.Sheets.get_Item(wb.Sheets.Count);

			Excel.Worksheet sh =  wb.Sheets.Add(Type.Missing, last, 1, Excel.XlSheetType.xlWorksheet);
			
			return sh;
		}

		public static Excel.Worksheet ActiveSheet()
		{
			return Globals.ThisAddIn.Application.ActiveWorkbook.ActiveSheet;
		}

		public static Excel.Workbook ActiveBook()
		{
			return Globals.ThisAddIn.Application.ActiveWorkbook;
		}
		public static void ShowError(string error)
		{
			MessageBox.Show(error, "出错啦", MessageBoxButtons.OK, MessageBoxIcon.Error);
		}

		public static bool SetCustomProp(Excel.Workbook wb, string key, object val)
		{
			Office.DocumentProperties properties = (Office.DocumentProperties)wb.CustomDocumentProperties;

			if (GetCustomProp(wb, key) != null)
			{
				properties[key].Delete();

			}

			properties.Add(key, false, Office.MsoDocProperties.msoPropertyTypeString, val, Type.Missing);
			
			return true;

		}
		public static object GetCustomProp(Excel.Workbook wb, string key)
		{
			Office.DocumentProperties properties = (Office.DocumentProperties)wb.CustomDocumentProperties;

			foreach (Office.DocumentProperty prop in properties)
			{
				if (prop.Name == key)
				{
					return prop.Value.ToString();
				}
			}
			return null;
		}
	}
}
