#pragma once


namespace engine
{
	class EXPORT_CLASS GameObjectComponent
	{
	public:
		GameObjectComponent(void);
		virtual ~GameObjectComponent(void);


		virtual void				Update();

		void						Attach(GameObjectPtr pObject);
		
		const std::string&			GetName();


	protected:
		GameObjectPtr				m_pObject;
		std::string					m_name;
	};
}
