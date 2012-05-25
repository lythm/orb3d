using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameEntity
{
	public abstract class EntityDescriptor 
	{
		public abstract Entity CreateEntity();

		public abstract void DestroyEntity(Entity entity);
	}

	public class ItemEntityDescriptor : EntityDescriptor
	{
		public override Entity CreateEntity()
		{
			Entity e = new Entity();

			e.PropertyMap["item_property"] = new ItemEntityProperty();

			return e;
		}

		public override void DestroyEntity(Entity entity)
		{
			throw new NotImplementedException();
		}
	}

}
