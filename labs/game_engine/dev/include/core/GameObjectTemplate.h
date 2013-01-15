#pragma once

namespace ld3d
{
	class EXPORT_CLASS GameObjectTemplate
	{
	public:
		GameObjectTemplate(GameObjectManagerPtr pManager, const std::wstring& name, const std::wstring& catalog = std::wstring(L"Misc"));
		virtual ~GameObjectTemplate(void);

		const std::wstring&						GetName();
		const std::wstring&						GetCataLog();

		void									SetName(const std::wstring& name);
		void									SetCataLog(const std::wstring& catalog);

		virtual GameObjectPtr					CreateGameObject()						= 0;
		virtual void							Release()								= 0;
	protected:

		GameObjectManagerPtr					m_pManager;
		std::wstring							m_name;
		std::wstring							m_catalog;
	};
}
