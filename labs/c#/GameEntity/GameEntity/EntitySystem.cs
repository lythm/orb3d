using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameEntity
{
	public class EntitySystem
	{
		public Dictionary<string, EntityDescriptor> EntityDescMap;

		public EntitySystem()
		{
			EntityDescMap = new Dictionary<string, EntityDescriptor>();

		}

		public Entity CreateEntity(string EntityName)
		{
			EntityDescriptor desc = EntityDescMap[EntityName];

			if (desc == null)
				return null;

			return desc.CreateEntity();
		}

		public void DestroyEntity(Entity entity)
		{

		}
	}
}
