using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace EntityEditor
{
	
	public partial class PropertyForm : Form
	{
		PropertyPack.PropertyTable pack;
		public PropertyForm()
		{
			InitializeComponent();


			GameEntity.EntitySystem es = new GameEntity.EntitySystem();

			es.EntityDescMap["ItemEntity"] = new GameEntity.ItemEntityDescriptor();

			GameEntity.Entity e = es.CreateEntity("ItemEntity");

			pack = new PropertyPack.PropertyTable();

			pack.Properties.Add(new PropertyPack.PropertySpec("age", typeof(int)));
			pack.Properties.Add(new PropertyPack.PropertySpec("name", typeof(string)));
			
			propGrid.SelectedObject = pack;
		}
	}
}
