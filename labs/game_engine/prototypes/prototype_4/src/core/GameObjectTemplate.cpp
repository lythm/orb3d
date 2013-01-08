#include "core_pch.h"
#include "..\..\include\core\GameObjectTemplate.h"
#include "core\DataStream_Mem.h"

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
	GameObjectPtr GameObjectTemplate::CreateObject()
	{

		return GameObjectPtr();
	}
	bool GameObjectTemplate::CreateFromGameObject(GameObjectPtr pObj)
	{
		return true;
	}
	void GameObjectTemplate::Release()
	{
		if(m_pData)
		{
			m_pData->Close();
			m_pData.reset();
		}
	}
}
