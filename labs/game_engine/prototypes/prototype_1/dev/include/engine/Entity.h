#pragma once

namespace engine
{
	class EntityComponent;

	class Entity
	{
	public:
		Entity(void);
		virtual ~Entity(void);

		void													AddComponent(const std::string& name, boost::shared_ptr<EntityComponent> pCom);
		
		boost::shared_ptr<EntityComponent>						FindComponent(const std::string& name);


	private:

		boost::unordered_map<std::string, 
			boost::shared_ptr<EntityComponent> >				m_Coms;
	};

}
