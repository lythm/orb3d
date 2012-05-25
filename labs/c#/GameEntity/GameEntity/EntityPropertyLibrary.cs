using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameEntity
{
	public abstract class EntityPropertyLibrary
	{
		public string Name { get; set; }

		public abstract bool Register(EntitySystem system);
		

	}
}
