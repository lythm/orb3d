#pragma once

#include <boost\enable_shared_from_this.hpp>
namespace engine
{
	class EXPORT_CLASS GameObjectComponent: public boost::enable_shared_from_this<GameObjectComponent>
	{
	public:
		GameObjectComponent(const std::wstring& name);
		virtual ~GameObjectComponent(void);
		
		virtual void				Update();

		virtual bool				Attach(GameObjectPtr pObject);
		virtual void				Detach();


		const std::wstring&			GetName();

		void						SetName(const std::wstring& name);

		GameObjectPtr				GetGameObject();
	private:
		virtual bool				OnAttach();
		virtual void				OnDetach();
		
	protected:
		GameObjectPtr				m_pObject;
		std::wstring				m_name;
	};
}
