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

		void						SetName(const std::wstring& name);
	private:
		virtual void				OnAttach();
		virtual void				OnDetach();
		
	protected:
		GameObjectPtr				m_pObject;
		std::wstring				m_name;
	};
}
