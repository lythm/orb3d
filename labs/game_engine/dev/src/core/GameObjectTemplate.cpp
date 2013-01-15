#include "core_pch.h"
#include "..\..\include\core\GameObjectTemplate.h"
#include "core\DataStream_Mem.h"
#include "core_utils.h"

namespace ld3d
{
	GameObjectTemplate::GameObjectTemplate(GameObjectManagerPtr pManager, const std::wstring& name, const std::wstring& catalog)
	{
		m_pManager = pManager;
		m_name = name;
		m_catalog = catalog;
	}


	GameObjectTemplate::~GameObjectTemplate(void)
	{
		m_pManager.reset();
	}
	const std::wstring& GameObjectTemplate::GetName()
	{
		return m_name;
	}
	void GameObjectTemplate::SetName(const std::wstring& name)
	{
		m_name = name;
	}
	void GameObjectTemplate::SetCataLog(const std::wstring& catalog)
	{
		m_catalog = catalog;
	}
	const std::wstring& GameObjectTemplate::GetCataLog()
	{
		return m_catalog;
	}
}
