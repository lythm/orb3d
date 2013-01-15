#pragma once

#include <boost\enable_shared_from_this.hpp>
namespace engine
{
	class EXPORT_CLASS GameObjectComponent: public boost::enable_shared_from_this<GameObjectComponent>
	{
	public:
		GameObjectComponent(const std::wstring& name, GameObjectManagerPtr pManager);
		GameObjectComponent(GameObjectManagerPtr pManager);
		virtual ~GameObjectComponent(void);
		
		virtual void				Update();

		virtual bool				Attach(GameObjectPtr pObject);
		virtual void				Detach();

		virtual void				OnComponentAttached(GameObjectComponentPtr pCom);
		virtual void				OnComponentDetached(GameObjectComponentPtr pCom);

		virtual bool				Serialize(DataStream* pStream);
		virtual void				UnSerialize(DataStream* pStream);

		
		const std::wstring&			GetName();

		void						SetName(const std::wstring& name);

		GameObjectPtr				GetGameObject();

		GameObjectManagerPtr		GetGameObjectManager();

		virtual bool				IsExclusive();

		virtual GameObjectComponentPtr Clone();
		
	private:
		virtual bool				OnAttach();
		virtual void				OnDetach();
		
	protected:
		GameObjectPtr				m_pObject;
		std::wstring				m_name;
		GameObjectManagerPtr		m_pManager;

	};
}
