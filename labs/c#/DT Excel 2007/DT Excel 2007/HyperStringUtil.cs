using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Text.RegularExpressions;

namespace DT_Excel_2007
{
	public class HyperStringUtil
	{
		public enum HyperType
		{
			text,
			graph,
			item,
			quest,
			textlink,
			url,
			playername,
			char_name,
			char_pro,
			map,
			waypoint,
			mob,
			questvalue,
			skilllink,
			newline,
			bidding,
		};

		public string Delimiter_Begin { get; set; }
		public string Delimiter_End { get; set; }


		public HyperStringUtil()
		{
			Delimiter_Begin = "{";
			Delimiter_End = "}";
		}

		public string MakeItemLinkTemplate()
		{
			return "{item:0}";
		}
		public string MakeMobLinkTemplate()
		{
			return "{mob:0}";	
		}
		public string MakeMapLinkTemplate()
		{
			return "{map:0,name}";
		}
		public string MakeWaypointLinkTemplate()
		{
			return "{waypoint:0,name}";
		}
		public string MakeCharNameLinkTemplate()
		{
			return "{char_name}";
		}
		public string MakeCharProLinkTemplate()
		{
			return "{char_pro}";
		}
		public string MakeNewlineLinkTemplate()
		{
			return "{newline}";
		}

		public bool HS_Correct(ref string str)
		{
			string[] l = Regex.Split(str, @"([\{][^\{]*[\}])");

			string ret = "";

			bool corrected = false;

			for (int i = 0; i < l.Length; ++i)
			{
				if (l[i] == "")
					continue;

				string tmp = l[i];
				if (true == Element_correct(ref tmp))
				{
					corrected = true;
				}
				ret += tmp;
			}

			str = ret;
			return corrected;
		}

		public bool Element_correct(ref string str)
		{
			if (str[0] != '{')
			{
				return false;
			}

			if (str.Length < 2)
			{
				throw new Exception("无效的HyperLink定义");
			}

			string naked = str;

			naked = naked.Substring(1);
			naked = naked.Substring(0, naked.Length - 1);

			if (naked == "")
			{
				throw new Exception("无效的HyperLink定义");
			}

			if (naked.Contains('{') || naked.Contains('}'))
			{
				throw new Exception("无效的HyperLink定义：{}嵌套使用。");
			}


			string[] subs = Regex.Split(naked, @"[:]");

			if (subs.Length == 0)
			{
				throw new Exception("无法识别的HyperLink");
			}

			bool ret = false;

			switch (subs[0])
			{
				case "item":
				case "i":
					ret = Item_correct(ref naked);
					break;
				case "mob":
				case "mb":
					ret = Mob_correct(ref naked);
					break;
				case "map":
				case "mp":
					ret = Map_correct(ref naked);
					break;
				case "waypoint":
				case "wp":
					ret = Waypoint_correct(ref naked);
					break;
				case "char_name":
				case "cn":
					ret = false;
					break;
				case "char_pro":
				case "cp":
					ret = false;
					break;
				case "newline":
				case "nl":
					ret = false;
					break;
				default:
					throw new Exception("无法识别的HyperLink");
			}

			str = "{" + naked + "}";
			return ret;
		}

		public bool Waypoint_correct(ref string str)
		{
			string[] subs = Regex.Split(str, @"[:]");

			if (subs.Length < 2 || subs[0] == "")
			{
				throw new Exception("无效的waypoint定义: 参数不够");
			}

			string[] args = Regex.Split(subs[1], @",");

			if (args.Length < 1)
			{
				throw new Exception("无效的waypoint定义: 参数不够");
			}

			if (args[0] == "")
			{
				throw new Exception("无效的waypoint定义: 参数错误");
			}

			UInt32 id = Convert.ToUInt32(args[0]);

			bool ret = false;
			string name = Utils.GetWaypointName(id);

			if (name == "")
			{
				throw new Exception("找不到waypoint[" + id + "]或者waypoint的名字");
			}

			if (args.Length >= 2)
			{
				if (name != args[1])
				{
					ret = true;
				}
			}
			else
			{
				ret = true;
			}

			str = "waypoint:" + id + "," + name;

			return ret;
		}

		public bool Map_correct(ref string str)
		{
			string[] subs = Regex.Split(str, @"[:]");

			if (subs.Length < 2 || subs[0] == "")
			{
				throw new Exception("无效的map定义: 参数不够");
			}

			string[] args = Regex.Split(subs[1], @",");

			if (args.Length < 1)
			{
				throw new Exception("无效的map定义: 参数不够");
			}

			if (args[0] == "")
			{
				throw new Exception("无效的map定义: 参数错误");
			}

			UInt32 id = Convert.ToUInt32(args[0]);

			bool ret = false;
			string name = Utils.GetMapName(id);

			if (name == "")
			{
				throw new Exception("找不到map[" + id + "]或者map的名字");
			}

			if (args.Length >= 2)
			{
				if (name != args[1])
				{
					ret = true;
				}
			}
			else
			{
				ret = true;
			}

			str = "map:" + id + "," + name;

			return ret;
		}

		public bool Mob_correct(ref string str)
		{
			string[] subs = Regex.Split(str, @"[:]");

			if (subs.Length < 2 || subs[0] == "")
			{
				throw new Exception("无效的mob定义: 参数不够");
			}

			string[] args = Regex.Split(subs[1], @",");

			if (args.Length < 1)
			{
				throw new Exception("无效的mob定义: 参数不够");
			}

			if (args[0] == "")
			{
				throw new Exception("无效的mob定义: 参数错误");
			}

			UInt32 id = Convert.ToUInt32(args[0]);

			bool ret = false;
			string name = Utils.GetMobName(id);

			if (name == "")
			{
				throw new Exception("找不到怪物["+id+"]或者怪物的名字");
			}

			if (args.Length >= 2)
			{
				if (name != args[1])
				{
					ret = true;
				}
			}
			else
			{
				ret = true;
			}

			str = "mob:" + id + "," + name;

			return ret;
		}
		public bool Item_correct(ref string str)
		{
			string[] subs = Regex.Split(str, @"[:]");

			if (subs.Length < 2 || subs[0] == "")
			{
				throw new Exception("无效的item定义: 参数不够");
			}

			string[] args = Regex.Split(subs[1], @",");

			if (args.Length < 1)
			{
				throw new Exception("无效的item定义: 参数不够");
			}

			if (args[0] == "")
			{
				throw new Exception("无效的item定义: 参数错误");
			}

			UInt32 id = Convert.ToUInt32(args[0]);

			string name = Utils.GetItemName(id);

			if (name == "")
			{
				throw new Exception("找不到物品[" + id + "]或者物品的名字");
			}

			bool ret = false;
			if (args.Length >= 2)
			{
				if (name != args[1])
				{
					ret = true;
				}
			}
			else
			{
				ret = true;
			}

			str = "item:" + id + "," + name;

			return ret;
		}

		public string HS_preview(string str)
		{
			string[] l = Regex.Split(str, @"([\{][^\{]*[\}])");

			string ret = "";

			for (int i = 0; i < l.Length; ++i)
			{
				if (l[i] == "")
					continue;

				ret += Element_preview(l[i]);
			}

			return ret;
		}

		public string Element_preview(string str)
		{
			if (str[0] != '{')
			{
				return Text_preview(str);
			}

			if (str.Length < 2)
			{
				throw new Exception("无效的HyperLink定义");
			}

			string naked = str;

			naked = naked.Substring(1);
			naked = naked.Substring(0, naked.Length - 1);

			if (naked == "")
			{
				throw new Exception("无效的HyperLink定义");
			}

			if (naked.Contains('{') || naked.Contains('}'))
			{
				throw new Exception("无效的HyperLink定义：{}嵌套使用。");
			}


			string[] subs = Regex.Split(naked, @"[:]");

			if (subs.Length == 0)
			{
				throw new Exception("无法识别的HyperLink");
			}

			string ret = "";

			switch (subs[0])
			{
				case "item":
				case "i":
					ret = Item_preview(naked);
					break;
				case "mob":
				case "mb":
					ret = Mob_preview(naked);
					break;
				case "map":
				case "mp":
					ret = Map_preview(naked);
					break;
				case "waypoint":
				case "wp":
					ret = Waypoint_preview(naked);
					break;
				case "char_name":
				case "cn":
					ret = CharName_preview(naked);
					break;
				case "char_pro":
				case "cp":
					ret = CharPro_preview(naked);
					break;
				case "newline":
				case "nl":
					ret = Newline_preview(naked);
					break;
				default:
					throw new Exception("无法识别的HyperLink");
			}
			return ret;
		}
		public string Newline_preview(string str)
		{
			return "\n";
		}
		public string CharPro_preview(string str)
		{
			return "【战士】";
		}
		public string CharName_preview(string str)
		{
			return "【滚键盘的脸】";
		}
		public string Waypoint_preview(string str)
		{
			string[] subs = Regex.Split(str, @"[:]");

			if (subs.Length < 2 || subs[0] == "")
			{
				throw new Exception("无效的waypoint定义: 参数不够");
			}

			string[] args = Regex.Split(subs[1], @",");

			if (args.Length < 1)
			{
				throw new Exception("无效的waypoint定义: 参数不够");
			}

			if (args[0] == "")
			{
				throw new Exception("无效的waypoint定义: 参数错误");
			}

			UInt32 id = Convert.ToUInt32(args[0]);

			string name = Utils.GetWaypointName(id);
			if (args.Length >= 2)
			{
				if (name != args[1])
				{
					throw new Exception("【" + args[1] + "==>" + name + "】");
				}
			}
			
			return "【" + name + "】";
		}


		public string Map_preview(string str)
		{
			string[] subs = Regex.Split(str, @"[:]");

			if (subs.Length < 2 || subs[0] == "")
			{
				throw new Exception("无效的map定义: 参数不够");
			}

			string[] args = Regex.Split(subs[1], @",");

			if (args.Length < 1)
			{
				throw new Exception("无效的map定义: 参数不够");
			}

			if (args[0] == "")
			{
				throw new Exception("无效的map定义: 参数错误");
			}

			UInt32 id = Convert.ToUInt32(args[0]);

			string name = Utils.GetMapName(id);
			if (args.Length >= 2)
			{
				if (name != args[1])
				{
					throw new Exception("【" + args[1] + "==>" + name + "】");
				}
			}

			return "【" + name + "】";
		}
		public string Mob_preview(string str)
		{
			string[] subs = Regex.Split(str, @"[:]");

			if (subs.Length < 2 || subs[0] == "")
			{
				throw new Exception("无效的mob定义: 参数不够");
			}

			string[] args = Regex.Split(subs[1], @",");

			if (args.Length < 1)
			{
				throw new Exception("无效的mob定义: 参数不够");
			}

			if (args[0] == "")
			{
				throw new Exception("无效的mob定义: 参数错误");
			}

			UInt32 id = Convert.ToUInt32(args[0]);

			string name = Utils.GetMobName(id);
			if (args.Length >= 2)
			{
				if (name != args[1])
				{
					throw new Exception("【" + args[1] + "==>" + name + "】");
				}
			}
			
			return "【" + name + "】";
		}
		public string Item_preview(string str)
		{
			string[] subs = Regex.Split(str, @"[:]");

			if (subs.Length < 2 || subs[0] == "")
			{
				throw new Exception("无效的item定义: 参数不够");
			}

			string[] args = Regex.Split(subs[1], @",");

			if (args.Length < 1)
			{
				throw new Exception("无效的item定义: 参数不够");
			}

			if (args[0] == "")
			{
				throw new Exception("无效的item定义: 参数错误");
			}

			UInt32 id = Convert.ToUInt32(args[0]);

			string name = Utils.GetItemName(id);
			if (args.Length >= 2)
			{
				if (name != args[1])
				{
					throw new Exception("【" + args[1] + "==>" + name + "】");
				}
			}
			
			return "【" + name + "】";
		}
		public string Text_preview(string str)
		{
			if (str.Contains('{') || str.Contains('}'))
			{
				throw new Exception("字符串中包含保留字符: { 或者 }， 很可能是由于没有配对使用大括号导致的。");
			}

			return str;

		}


		/// <summary>
		/// //////////////
		/// </summary>
		/// <param name="str"></param>
		/// <returns></returns>

		public byte[] HS_str2b(string str, bool checking)
		{
			MemoryStream ms = new MemoryStream();
			BinaryWriter bw = new BinaryWriter(ms);


			string[] l = Regex.Split(str, @"([\{][^\{]*[\}])");


			UInt32 nElm = 0;

			bw.Write(nElm);
			
			for (int i = 0; i < l.Length; ++i)
			{
				if(l[i] == "")
					continue;

				byte[] data = Element_str2b(l[i], checking);
				
				bw.Write(data);
				nElm++;
			}

			bw.Seek(0, SeekOrigin.Begin);
			bw.Write(nElm);
			
			return ms.ToArray();
		}

		public byte[] Element_str2b(string str, bool checking)
		{

			if (str[0] != '{')
			{
				return Text_str2b(str, checking);
			}

			if (str.Length < 2)
			{
				throw new Exception("无效的HyperLink定义");
			}

			string naked = str;

			naked = naked.Substring(1);
			naked = naked.Substring(0, naked.Length - 1);

			if (naked == "")
			{
				throw new Exception("无效的HyperLink定义");
			}

			if (naked.Contains('{') || naked.Contains('}'))
			{
				throw new Exception("无效的HyperLink定义: 嵌套使用{}");
			}


			string[] subs = Regex.Split(naked, @"[:]");

			if (subs.Length == 0)
			{
				throw new Exception("无法识别的HyperLink");
			}
						
			byte[] data = null;

			switch (subs[0])
			{
				case "item":
				case "i":
					data = Item_str2b(naked, checking);
					break;
				case "mob":
				case "mb":
					data = Mob_str2b(naked, checking);
					break;
				case "map":
				case "mp":
					data = Map_str2b(naked, checking);
					break;
				case "waypoint":
				case "wp":
					data = Waypoint_str2b(naked, checking);
					break;
				case "char_name":
				case "cn":
					data = CharName_str2b(naked, checking);
					break;
				case "char_pro":
				case "cp":
					data = CharPro_str2b(naked, checking);
					break;
				case "newline":
				case "nl":
					data = Newline_str2b(naked, checking);
					break;
				default:
					throw new Exception("无法识别的HyperLink");
			}
			return data;
		}
		public byte[] Newline_str2b(string str, bool checking)
		{
			string[] subs = Regex.Split(str, @"[:]");

			if (subs.Length == 0 || subs[0] == "")
			{
				throw new Exception("无效的newline定义");
			}

			MemoryStream ms = new MemoryStream();

			BinaryWriter bw = new BinaryWriter(ms);

			bw.Write((UInt32)HyperType.char_name);

			return ms.ToArray();
		}
		public byte[] CharPro_str2b(string str, bool checking)
		{
			string[] subs = Regex.Split(str, @"[:]");

			if (subs.Length == 0 || subs[0] == "")
			{
				throw new Exception("无效的char_pro定义");
			}

			MemoryStream ms = new MemoryStream();

			BinaryWriter bw = new BinaryWriter(ms);

			bw.Write((UInt32)HyperType.char_name);

			return ms.ToArray();
		}
		public byte[] CharName_str2b(string str, bool checking)
		{
			string[] subs = Regex.Split(str, @"[:]");

			if (subs.Length == 0 || subs[0] == "")
			{
				throw new Exception("无效的char_name定义");
			}

			MemoryStream ms = new MemoryStream();

			BinaryWriter bw = new BinaryWriter(ms);

			bw.Write((UInt32)HyperType.char_name);
			
			return ms.ToArray();
		}
		public byte[] Waypoint_str2b(string str, bool checking)
		{
			string[] subs = Regex.Split(str, @"[:]");

			if (subs.Length < 2 || subs[0] == "")
			{
				throw new Exception("无效的waypoint定义: 参数不够");
			}

			string[] args = Regex.Split(subs[1], @",");

			if (args.Length < 1)
			{
				throw new Exception("无效的waypoint定义: 参数不够");
			}

			if (args[0] == "")
			{
				throw new Exception("无效的waypoint定义: 参数不够");
			}

			UInt32 id = Convert.ToUInt32(args[0]);

			string name = "";

			if (checking == false)
			{
				if (args.Length >= 2)
				{
					name = args[1];
				}
				else
				{
					name = Utils.GetWaypointName(id);
				}
			}
			else
			{
				name = Utils.GetWaypointName(id);

				if (name == "")
				{
					throw new Exception("找不到waypoint[" + id + "] 或者waypoint的名字");
				}

				if (args.Length >= 2)
				{
					if (args[1] != name)
					{
						throw new Exception("waypoint名与脚本中的值不一致: " + args[1] + "(" + args[1].Length + ")" + "==>" + name + "(" + name.Length + ")");
					}
				}
			}

			UInt16 c = (UInt16)name.Length;

			byte[] data = UnicodeEncoding.Unicode.GetBytes(name);

			MemoryStream ms = new MemoryStream();

			BinaryWriter bw = new BinaryWriter(ms);

			bw.Write((UInt32)HyperType.map);
			bw.Write(c);
			bw.Write(data);

			bw.Write(id);

			return ms.ToArray();
		}
		public byte[] Map_str2b(string str, bool checking)
		{
			string[] subs = Regex.Split(str, @"[:]");

			if (subs.Length < 2 || subs[0] == "")
			{
				throw new Exception("无效的map定义: 参数不够");
			}

			string[] args = Regex.Split(subs[1], @",");

			if (args.Length < 1)
			{
				throw new Exception("无效的map定义: 参数不够");
			}

			if (args[0] == "")
			{
				throw new Exception("无效的map定义: 参数不够");
			}

			UInt32 id = Convert.ToUInt32(args[0]);

			string name = "";

			if (checking == false)
			{
				if (args.Length >= 2)
				{
					name = args[1];
				}
				else
				{
					name = Utils.GetMapName(id);
				}
			}
			else
			{
				name = Utils.GetMapName(id);

				if (name == "")
				{
					throw new Exception("找不到map[" + id + "] 或者map的名字");
				}

				if (args.Length >= 2)
				{
					if (args[1] != name)
					{
						throw new Exception("map名与脚本中的值不一致: " + args[1] + "(" + args[1].Length + ")" + "==>" + name + "(" + name.Length + ")");
					}
				}
			}


			UInt16 c = (UInt16)name.Length;

			byte[] data = UnicodeEncoding.Unicode.GetBytes(name);

			MemoryStream ms = new MemoryStream();

			BinaryWriter bw = new BinaryWriter(ms);

			bw.Write((UInt32)HyperType.map);
			bw.Write(c);
			bw.Write(data);

			bw.Write(id);

			return ms.ToArray();
		}
		public byte[] Mob_str2b(string str, bool checking)
		{
			string[] subs = Regex.Split(str, @"[:]");

			if (subs.Length < 2 || subs[0] == "")
			{
				throw new Exception("无效的mob定义: 参数不够");
			}

			string[] args = Regex.Split(subs[1], @",");

			if (args.Length < 1)
			{
				throw new Exception("无效的mob定义: 参数不够");
			}

			if (args[0] == "")
			{
				throw new Exception("无效的mob定义: 参数不够");
			}

			UInt32 id = Convert.ToUInt32(args[0]);


			string name = "";

			if (checking == false)
			{
				if (args.Length >= 2)
				{
					name = args[1];
				}
				else
				{
					name = Utils.GetMobName(id);
				}
			}
			else
			{
				name = Utils.GetMobName(id);

				if (name == "")
				{
					throw new Exception("找不到怪物[" + id + "] 或者怪物的名字");
				}

				if (args.Length >= 2)
				{
					if (args[1] != name)
					{
						throw new Exception("怪物名与脚本中的值不一致: " + args[1] + "(" + args[1].Length + ")" + "==>" + name + "(" + name.Length + ")");
					}
				}

			}

			UInt16 c = (UInt16)name.Length;

			byte[] data = UnicodeEncoding.Unicode.GetBytes(name);

			MemoryStream ms = new MemoryStream();

			BinaryWriter bw = new BinaryWriter(ms);

			bw.Write((UInt32)HyperType.mob);
			bw.Write(c);
			bw.Write(data);

			bw.Write(id);
			
			return ms.ToArray();
		}
		public byte[] Item_str2b(string str, bool checking)
		{
			string[] subs = Regex.Split(str, @"[:]");

			if (subs.Length < 2 || subs[0] == "")
			{
				throw new Exception("无效的item定义: 参数不够");
			}

			string[] args = Regex.Split(subs[1], @",");

			if (args.Length < 1)
			{
				throw new Exception("无效的item定义: 参数不够");
			}

			if (args[0] == "")
			{
				throw new Exception("无效的item定义: 参数不够");
			}

			UInt32 id0 = Convert.ToUInt32(args[0]);
			UInt32 id1 = 0;


			string name = "";

			if (checking == false)
			{
				if (args.Length >= 2)
				{
					name = args[1];
				}
				else
				{
					name = Utils.GetItemName(id0);
				}
			}
			else
			{
				name = Utils.GetItemName(id0);

				if (name == "")
				{
					throw new Exception("找不到物品[" + id0 + "] 或者物品的名字");
				}

				if (args.Length >= 2)
				{
					if (args[1] != name)
					{
						throw new Exception("物品名与脚本中的值不一致: " + args[1] + "(" + args[1].Length + ")" + "==>" + name +"(" + name.Length + ")");
					}
				}

			}

			UInt16 c = (UInt16)name.Length;

			byte[] data = UnicodeEncoding.Unicode.GetBytes(name);

			MemoryStream ms = new MemoryStream();

			BinaryWriter bw = new BinaryWriter(ms);

			bw.Write((UInt32)HyperType.item);
			bw.Write((byte)1);
			bw.Write(c);
			bw.Write(data);
			
			bw.Write(id0);
			bw.Write(id1);
			
			return ms.ToArray();
		}
		public byte[] Text_str2b(string str, bool checking)
		{
			if (str.Contains('{') || str.Contains('}'))
			{
				throw new Exception("字符串中包含保留字符: { 或者 }， 很可能是由于没有配对使用大括号导致的。");
			}

			UInt16 c = (UInt16)str.Length;

			byte[] data = UnicodeEncoding.Unicode.GetBytes(str);

			MemoryStream ms = new MemoryStream();

			BinaryWriter bw = new BinaryWriter(ms);

			bw.Write((UInt32)HyperType.text);
			bw.Write(c);
			bw.Write(data);

			return ms.ToArray();
		}

		public string HS_b2str(byte[] data)
		{
			string ret = "";
			MemoryStream ms = new MemoryStream(data);

			BinaryReader br = new BinaryReader(ms, UnicodeEncoding.Unicode);

			UInt32 nElm = br.ReadUInt32();

			for (ulong i = 0; i < nElm; ++i)
			{
				ret += Element_b2str(br);
			}

			return ret;

		}
		public string Element_b2str(BinaryReader br)
		{
			UInt32 type = br.ReadUInt32();

			string tag = "";

			switch ((HyperType)type)
			{
				case HyperType.item:
					tag = Item_b2str(br);
					break;
				case HyperType.text:
					tag = Text_b2str(br);
					break;
				case HyperType.newline:
					tag = NewLine_b2str(br);
					break;
				case HyperType.map:
					tag = Map_b2str(br);
					break;
				case HyperType.mob:
					tag = Mob_b2str(br);
					break;
				case HyperType.waypoint:
					tag = Waypoint_b2str(br);
					break;
				case HyperType.char_name:
					tag = CharName_b2str(br);
					break;
				case HyperType.char_pro:
					tag = CharPro_b2str(br);
					break;

				default:
					tag = "!未可知!";
					break;
			}

			if (type == (UInt32)HyperType.text)
			{
				return tag;
			}

			return Delimiter_Begin + tag + Delimiter_End;
		}

		public string Text_b2str(BinaryReader br)
		{

			UInt16 c = br.ReadUInt16();

			byte[] s = br.ReadBytes(c * sizeof(UInt16));

			return UnicodeEncoding.Unicode.GetString(s);
		}
		public string Item_b2str(BinaryReader br)
		{
			string ret = "";

			br.ReadByte();

			UInt16 c = br.ReadUInt16();

			byte[] s = br.ReadBytes(c * sizeof(UInt16));

			string name = UnicodeEncoding.Unicode.GetString(s);

			UInt32 id0 = br.ReadUInt32();
			UInt32 id1 = br.ReadUInt32();


			ret = "item:" + id0 + "," + name;

			return ret;

		}

		public string Mob_b2str(BinaryReader br)
		{
			UInt16 c = br.ReadUInt16();

			byte[] s = br.ReadBytes(c * sizeof(UInt16));

			string name = UnicodeEncoding.Unicode.GetString(s);

			UInt32 id = br.ReadUInt32();

			string ret = "mob:" + id + "," + name;

			return ret;
		}

		public string Map_b2str(BinaryReader br)
		{
			UInt16 c = br.ReadUInt16();
			
			byte[] s = br.ReadBytes(c * sizeof(UInt16));

			string name = UnicodeEncoding.Unicode.GetString(s);

			UInt32 id = br.ReadUInt32();

			string ret = "map:" + id + "," + name;

			return ret;
		}

		public string Waypoint_b2str(BinaryReader br)
		{
			UInt16 c = br.ReadUInt16();

			byte[] s = br.ReadBytes(c * sizeof(UInt16));

			string name = UnicodeEncoding.Unicode.GetString(s);

			UInt32 id = br.ReadUInt32();

			string ret = "waypoint:" + id + "," + name;

			return ret;
		}

		public string CharName_b2str(BinaryReader br)
		{
			return "char_name:";
		}

		public string CharPro_b2str(BinaryReader br)
		{
			return "char_pro:";
		}

		public string NewLine_b2str(BinaryReader br)
		{
			return "newline:";
		}
	}
}
