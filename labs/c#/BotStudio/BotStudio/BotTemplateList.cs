using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LuaInterface;
using System.IO;
using System.Configuration;
namespace BotStudio
{
	public class BotTemplateList
	{
		public class Node
		{
			public enum NodeType
			{
				type_file,
				type_folder,
				type_root,
			}

			public Node(string val, Node parent, NodeType type)
			{
				Value = val;
				Type = type;
				Parent = parent;
				Children = new List<Node>();
			}
			public List<Node> Children{get;set;}
			public string Value{get;set;}
			public NodeType Type { get; set; }
			public Node Parent { get; set; }
		};

		public Node RootNode;
		public delegate void Event_OnUpdate();

		public Event_OnUpdate OnUpdate { get; set; }

		public BotTemplateList()
		{
			Clear();
		}

		public void Clear()
		{
			RootNode = new Node(ConfigurationManager.AppSettings["BotRoot"], null, Node.NodeType.type_folder);
		}
		public void Update()
		{
			Clear();

			if (Directory.Exists(ConfigurationManager.AppSettings["BotRoot"]) == false)
			{
				AppContext.WriteLog(ConfigurationManager.AppSettings["BotRoot"] + " does not exist.");
				
			}
			else
			{
				UpdateTemplateTree(ConfigurationManager.AppSettings["BotRoot"], RootNode);
			}

			if (OnUpdate != null)
			{
				OnUpdate();
			}
		}

		private bool IsBotTemplate(string file)
		{
			LuaInterface.Lua lua = new LuaInterface.Lua();

			
			try
			{

				lua.DoFile(file);

				LuaFunction on_event = lua.GetFunction("OnEvent");

				if(on_event == null)
					return false;

				

				return true;
			}
			catch (Exception e)
			{
				AppContext.WriteLog(e.Message);
				return false;
			}
		}
		
		private int UpdateTemplateTree(string rootDir, Node root)
		{
			if (Directory.Exists(rootDir) == false)
				return 0;

			string[] files = Directory.GetFiles(rootDir, "*.lua");

			int nFilesInFolder = 0;
			for (int i = 0; i < files.Length; ++i)
			{
				if(IsBotTemplate(files[i]) == false)
				{
					AppContext.WriteLog("Invalid bot script : " + files[i]);
					continue;
				}

				Node node = new Node(files[i], root, Node.NodeType.type_file);

				root.Children.Add(node);

				nFilesInFolder ++;
				AppContext.WriteLog("Bot loaded : " + files[i]);
			}

			string[] dirs = Directory.GetDirectories(rootDir);

			for (int i = 0; i < dirs.Length; ++i)
			{
				Node folder_node = new Node(dirs[i], root, Node.NodeType.type_folder);

				int nFiles = UpdateTemplateTree(dirs[i], folder_node);

				if (nFiles != 0)
				{
					
					root.Children.Add(folder_node);
				}
			}
			return nFilesInFolder;
		}
	}
}
