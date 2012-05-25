#pragma once

#include "core\Extension.h"



namespace engine
{
	class Ext_Core : public Extension
	{
	public:
		Ext_Core(void);
		virtual ~Ext_Core(void);


		GameObjectComponent*					CreateComponent(const char* szName);
		void									DestroyComponent(GameObjectComponent* pCom);
	};


}