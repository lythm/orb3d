#include "Ext_Core.h"

namespace engine
{
	Ext_Core::Ext_Core(void)
	{
	}


	Ext_Core::~Ext_Core(void)
	{
	}
	GameObjectComponent* Ext_Core::CreateComponent(const char* szName)
	{
		return 0;
	}
	void Ext_Core::DestroyComponent(GameObjectComponent* pCom)
	{
		//delete pCom;
	}
}
