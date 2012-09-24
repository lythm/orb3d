#pragma once


#include "WinApp.h"

namespace engine
{
	class EngineApp : public WinApp
	{
	public:
		EngineApp(void);
		virtual ~EngineApp(void);

		void											OnUpdate();
		bool											OnInit();
		void											OnRelease();


	private:
		
		void											ShowFPS();

	private:

		GameObjectManagerPtr							m_pObjectManager;


		SysManagerPtr									m_pSysManager;

		Sys_InputPtr									m_pSysInput;
	};


}
