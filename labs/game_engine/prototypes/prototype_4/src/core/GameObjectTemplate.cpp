#include "core_pch.h"
#include "..\..\include\core\GameObjectTemplate.h"

namespace engine
{
	GameObjectTemplate::GameObjectTemplate(const std::wstring& name)
	{
		SetName(name);
	}


	GameObjectTemplate::~GameObjectTemplate(void)
	{
	}
	const std::wstring&	GameObjectTemplate::GetName()
	{
		return m_name;
	}
	void GameObjectTemplate::SetName(const std::wstring& name)
	{
		m_name = name;
	}

}