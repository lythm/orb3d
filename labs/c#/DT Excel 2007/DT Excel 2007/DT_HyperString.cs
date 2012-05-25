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
	static class DT_HyperString
	{
		static HyperStringUtil FHSUtil = new HyperStringUtil();

		public static void AddTemplate_Item()
		{
			string tpl = FHSUtil.MakeItemLinkTemplate();
			
			Excel.Range sel = Utils.SelectedRange();

			if(sel.Count == 0)
				return;

			sel.Characters.Text += tpl;
		}
		public static void AddTemplate_Mob()
		{
			string tpl = FHSUtil.MakeMobLinkTemplate();

			Excel.Range sel = Utils.SelectedRange();

			if (sel.Count == 0)
				return;

			sel.Characters.Text += tpl;
		}

		public static void AddTemplate_Map()
		{
			string tpl = FHSUtil.MakeMapLinkTemplate();

			Excel.Range sel = Utils.SelectedRange();

			if (sel.Count == 0)
				return;

			sel.Characters.Text += tpl;
		}

		public static void AddTemplate_Waypoint()
		{
			string tpl = FHSUtil.MakeWaypointLinkTemplate();

			Excel.Range sel = Utils.SelectedRange();

			if (sel.Count == 0)
				return;

			sel.Characters.Text += tpl;
		}

		public static void AddTemplate_CharName()
		{
			string tpl = FHSUtil.MakeCharNameLinkTemplate();

			Excel.Range sel = Utils.SelectedRange();

			if (sel.Count == 0)
				return;

			sel.Characters.Text += tpl;
		}
		public static void AddTemplate_CharPro()
		{
			string tpl = FHSUtil.MakeCharProLinkTemplate();

			Excel.Range sel = Utils.SelectedRange();

			if (sel.Count == 0)
				return;

			sel.Characters.Text += tpl;
		}
		public static void AddTemplate_Newline()
		{
			string tpl = FHSUtil.MakeNewlineLinkTemplate();

			Excel.Range sel = Utils.SelectedRange();

			if (sel.Count == 0)
				return;

			sel.Characters.Text += tpl;
		}

		public static void Correct()
		{
			Utils.ReloadAssetsIfNot();

			Excel.Range sel = Utils.SelectedRange();

			int baseRow = sel.Row;
			int baseCol = sel.Column;


			Excel.Worksheet previewSh = Utils.CreateSheet();

			Dictionary<int, int> colWidth = new Dictionary<int, int>();
			
			int n_cor = 0;
			int n_err = 0;

			int irow = 2;

			foreach (Excel.Range cell in sel.Cells)
			{
				bool error = false;
				if (cell.Value2 != null)
				{
					Excel.Range target = previewSh.Cells[irow, cell.Column - baseCol + 1];

					string str = cell.Value2.ToString();

					bool corrected = false;
					try
					{
						corrected = FHSUtil.HS_Correct(ref str);
					}
					catch (Exception e)
					{
						n_err ++;
						error = true;
						str = " " + e.Message + " ";
					}
					if (corrected)
					{
						n_cor ++;
						cell.Value2 = str;
					}


					if(corrected == false && error == false)
						continue;

					//target.Value2 = str;
					previewSh.Hyperlinks.Add(target, "", cell.Worksheet.Name + "!" + cell.Address, Type.Missing, (corrected ? "已纠正: " : (error ? "无法纠正: " : "正确: ")) + str);

					if (error)
					{
						target.Font.Color = 0xff0000ff;
					}
					else if(corrected)
					{
						target.Font.Color = 0xfff00ff;
					}

					if (colWidth.ContainsKey(target.Column) == false)
					{
						colWidth.Add(target.Column, str.Length);
					}
					else
					{
						int w = colWidth[target.Column];

						if (str.Length > w)
						{
							w = str.Length;

							colWidth[target.Column] = w;
						}

					}
					irow++;
				}
			}

			previewSh.Cells[1, 1] = n_cor + "个被纠正   " + n_err + "个无法纠正";

			previewSh.UsedRange.Columns.HorizontalAlignment = Excel.XlHAlign.xlHAlignLeft;

			foreach (KeyValuePair<int, int> p in colWidth)
			{
				Utils.SetColoumWidth(previewSh, p.Key, p.Value * 2);
			}
		}
		public static void Preview()
		{
			Utils.ReloadAssetsIfNot();

			Excel.Range sel = Utils.SelectedRange();

			int baseRow = sel.Row;
			int baseCol = sel.Column;


			Excel.Worksheet previewSh = Utils.CreateSheet();

			Dictionary<int, int> colWidth = new Dictionary<int,int>();



			foreach (Excel.Range cell in sel.Cells)
			{
				bool error = false;
				if (cell.Value2 != null)
				{
					Excel.Range target = previewSh.Cells[cell.Row - baseRow + 1, cell.Column - baseCol + 1];

					string str = "";

					try
					{
						str = FHSUtil.HS_preview(cell.Value2.ToString());
					}
					catch (Exception e)
					{
						error = true;
						str = " " + e.Message + " ";
					}

					//target.Value2 = str;
					previewSh.Hyperlinks.Add(target, "", cell.Worksheet.Name + "!" + cell.Address, Type.Missing, str);
					
					if (error)
					{
						target.Font.Color = 0xff0000ff;
					}

					if (colWidth.ContainsKey(target.Column) == false)
					{
						colWidth.Add(target.Column, str.Length);
					}
					else
					{
						int w = colWidth[target.Column];

						if (str.Length > w)
						{
							w = str.Length;
							
							colWidth[target.Column] = w;
						}

					}
					
				}
			}

			previewSh.UsedRange.Columns.HorizontalAlignment = Excel.XlHAlign.xlHAlignLeft;

			foreach (KeyValuePair<int, int> p in colWidth)
			{
				Utils.SetColoumWidth(previewSh, p.Key, p.Value * 2);
			}
		}
		public static bool Import(Excel.Worksheet sheet, string file)
		{
			FileStream fs = File.Open(file, FileMode.Open);

			BinaryReader br = new BinaryReader(fs, UnicodeEncoding.Unicode);

			UInt32 tableId = br.ReadUInt32();

			UInt32 strCount = br.ReadUInt32();


			int max_text_len = 0;

			if (strCount == 0)
			{
				return true;
			}
			int irow = 1;
						
			for (ulong i = 0; i < strCount; ++i)
			{
				UInt32 nBytes = br.ReadUInt32();

				UInt32 id = br.ReadUInt32();

				sheet.Cells[irow, 1] = id;

				byte[] data = br.ReadBytes((int)(nBytes - 4));


				string str = FHSUtil.HS_b2str(data);
				
				sheet.Cells[i + 1, 2] = str;

				if (str.Length > max_text_len)
				{
					max_text_len = str.Length;
				}

				++irow;
			}

			sheet.UsedRange.Columns.HorizontalAlignment = Excel.XlHAlign.xlHAlignLeft;

			Utils.SetColoumWidth(sheet, 2, max_text_len);

			fs.Close();

			return true;
		}
		
		public static bool Export(Excel.Worksheet sheet, string file)
		{
			Utils.ReloadAssetsIfNot();

			FileStream fs = File.Create(file);

			BinaryWriter bw = new BinaryWriter(fs, UnicodeEncoding.Unicode);

			UInt32 tableId = 1;

			bw.Write(tableId);

			bw.Write((UInt32)0);

			Excel.Range ur = sheet.UsedRange;

			UInt32 count = 0;

			for (int rCnt = 1; rCnt <= ur.Rows.Count; rCnt++)
			{
				object id = ((ur.Cells[rCnt, 1] as Excel.Range).Value2);
				object v = ((ur.Cells[rCnt, 2] as Excel.Range).Value2);

				if (id == null)
				{
					continue;
				}

				UInt32 uid = Convert.ToUInt32(id.ToString());

				byte[] data = null;
				if (v == null)
				{
					UInt32 n = 0;

					data = BitConverter.GetBytes(n);		
				}
				else
				{
					data = FHSUtil.HS_str2b(v.ToString(), false);
				}

				if(data == null)
					continue;

				UInt32 bytes = (UInt32)(sizeof(UInt32) + data.Length);

				bw.Write(bytes);
				bw.Write(uid);
				bw.Write(data);

				count++;
			}

			bw.Seek(sizeof(UInt32), SeekOrigin.Begin);
			bw.Write(count);

			fs.Close();

			return true;
		}
		public static void Check(Excel.Worksheet sheet)
		{
			Utils.ReloadAssetsIfNot();

			Excel.Range ur = sheet.UsedRange;

			Dictionary<string, int> checkMap = new Dictionary<string, int>();
			
			List<string> idList = new List<string>();
			List<string> vList = new List<string>();
			List<string> eList = new List<string>();

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
					eList.Add("空字符串或者无效id");
					continue;
				}

				int x = 0;
				if (int.TryParse(id.ToString(), out x) == false)
				{
					idList.Add(sheet.Name + "!" + r1.Address);
					vList.Add(sheet.Name + "!" + r2.Address);
					eList.Add("无效id");
					continue;
				}

				try
				{
					FHSUtil.HS_str2b(v.ToString(), true);
				}
				catch (Exception _e)
				{
					idList.Add(sheet.Name + "!" + r1.Address);
					vList.Add(sheet.Name + "!" + r2.Address);
					eList.Add(_e.Message);
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
			sh.Cells[irow, 2] = "错误";
			sh.Cells[irow, 3] = "内容";

			++irow;

			for (int i = 0; i < idList.Count; ++i)
			{
				Excel.Range r = sh.Cells[irow, 1] as Excel.Range;
				sh.Hyperlinks.Add(r, "", idList[i], Type.Missing, "=" + idList[i]);


				r = sh.Cells[irow, 2] as Excel.Range;

				r.Value2 = eList[i];

				r = sh.Cells[irow, 3] as Excel.Range;

				sh.Hyperlinks.Add(r, "", vList[i], Type.Missing, "=" + vList[i]);

				++irow;
			}

			sh.Columns.HorizontalAlignment = Excel.XlHAlign.xlHAlignLeft;

			Utils.SetColoumWidth(sh, 1, 20);
			Utils.SetColoumWidth(sh, 2, 60);
			Utils.SetColoumWidth(sh, 3, 200);
		}
	}
}
