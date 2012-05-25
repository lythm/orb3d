using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameEntity
{
	public class Entity
	{
		public Dictionary<string, EntityProperty> PropertyMap 
		{ 
			get; 
			set; 
		}


		public Entity()
		{
			PropertyMap = new Dictionary<string, EntityProperty>();
		}

		public EntityProperty QueryProperty(string name)
		{
			return PropertyMap[name];
		}
	}
}
