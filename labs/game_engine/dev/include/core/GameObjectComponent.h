#pragma once

#include <boost\enable_shared_from_this.hpp>
namespace ld3d
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
		
		bool						Serialize(DataStream* pStream);
		bool						UnSerialize(DataStream* pStream);

		virtual bool				OnSerialize(DataStream* pStream);
		virtual bool				OnUnSerialize(DataStream* pStream, const Version& version);
		
		const std::wstring&			GetName();

		void						SetName(const std::wstring& name);

		GameObjectPtr				GetGameObject();

		GameObjectManagerPtr		GetGameObjectManager();

		virtual const Version&		GetVersion() const														= 0;

		const wchar_t*				GetVersionString();

		virtual GameObjectComponentPtr Clone();

		virtual const std::vector<std::wstring>&	GetDependences();
		virtual bool				IsExclusive();
		
	
	private:
		virtual bool				OnAttach();
		virtual void				OnDetach();
		
	protected:
		GameObjectPtr				m_pObject;
		std::wstring				m_name;
		GameObjectManagerPtr		m_pManager;
	};
}
