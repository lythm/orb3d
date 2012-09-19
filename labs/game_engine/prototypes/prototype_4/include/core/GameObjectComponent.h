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
		void						Detach();
		const std::wstring&			GetName();
		
	protected:
		GameObjectPtr				m_pObject;
		std::wstring				m_name;
	};
}
