#include "core_pch.h"
#include "..\..\include\core\GameObjectTemplate.h"
#include "core\DataStream_Mem.h"
#include "core_utils.h"

namespace engine
{
	GameObjectTemplate::GameObjectTemplate(GameObjectManagerPtr pManager)
	{
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
	GameObjectPtr GameObjectTemplate::CreateGameObject()
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
	bool GameObjectTemplate::Load(DataStreamPtr pStream)
	{
		return true;
	}
}
