#pragma once

namespace engine
{
	class Entity;

	class EntityManager
	{
	public:
		EntityManager(void);
		virtual ~EntityManager(void);

		boost::shared_ptr<Entity>					CreateEntity();
		void										DestroyEntity(boost::shared_ptr<Entity> pEntity);
		

	private:

	};


}