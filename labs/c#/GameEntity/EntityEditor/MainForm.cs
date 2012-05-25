using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Reflection;
using System.IO;

namespace EntityEditor
{
	public partial class MainForm : Form
	{
		public MainForm()
		{
			InitializeComponent();
		}

		private void button1_Click(object sender, EventArgs e)
		{

		
			//string dir = Directory.GetCurrentDirectory();

			//string fullpath = Path.Combine(dir, "./sampleentitypropertylib.dll");

			//Assembly assembly = Assembly.LoadFile(fullpath);

			//Type tp = assembly.GetType("SamplleEntityPropLib");
			//MethodInfo method = tp.GetMethod("Initialize");
			
			//bool ret = (bool)method.Invoke(null, new object[] { });


			//GameEntity.Entity ent = new GameEntity.Entity();


			//GameEntity.EntityProperty prop = ent.QueryProperty("aa");
		}
	}
}
