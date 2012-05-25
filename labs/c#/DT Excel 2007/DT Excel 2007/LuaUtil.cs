using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LuaInterface;
using System.Windows.Forms;
using System.IO;


namespace DT_Excel_2007
{
	public static class LuaUtil
	{
		public static Lua FLua = null;

		public static void Clear()
		{
			FLua = null;
		}
		public static bool Reload(string assets_root)
		{
			FLua = new Lua();

			string path = assets_root + "scripts/dt_all.lua";

			Directory.SetCurrentDirectory(assets_root + "../");

			FLua.DoFile(path);
			
			return true;
		}

		public static bool Reload()
		{
			object val = Utils.GetCustomProp(Utils.ActiveBook(), "EDT_assets_root");

			string assets_root = "";
			if (val != null)
			{
				assets_root = val.ToString();
			}

			return Reload(assets_root);
			
		}

		public static void ReloadIfNot()
		{
			if (FLua == null)
			{
				object val = Utils.GetCustomProp(Utils.ActiveBook(), "EDT_assets_root");

				string assets_root = "";
				if (val != null)
				{
					assets_root = val.ToString();
				}

				Reload(assets_root);
			}
		}

		public static int GetMapNameId(UInt32 map_id)
		{
			if (FLua == null)
				return -1;
			LuaFunction f = FLua.GetFunction("DT_GetMapNameId");
			object[] ret = f.Call(new object[] { map_id });

			return Convert.ToInt32(ret[0]);
		}
		public static int GetWaypointNameId(UInt32 wp_id)
		{
			if (FLua == null)
				return -1;
			LuaFunction f = FLua.GetFunction("DT_GetWaypointNameId");
			object[] ret = f.Call(new object[] { wp_id });

			return Convert.ToInt32(ret[0]);
		}
		public static int GetMobNameId(UInt32 mob_id)
		{
			if( FLua == null)
				return -1;
			LuaFunction f = FLua.GetFunction("DT_GetMobNameId");
			object[] ret = f.Call(new object[]{mob_id});

			return Convert.ToInt32(ret[0]);
		}

		public static int GetItemNameId(UInt32 item_id)
		{
			if (FLua == null)
				return -1;

			LuaFunction f = FLua.GetFunction("DT_GetItemNameId");
			object[] ret = f.Call(new object[] { item_id });

			return Convert.ToInt32(ret[0]);
		}
	}
}
