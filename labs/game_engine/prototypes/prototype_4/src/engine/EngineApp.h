#pragma once


#include "WinApp.h"

namespace engine
{
	class WMInput;
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

		void											HandleMessage(MSG& msg);
	private:

		GameObjectManagerPtr							m_pObjectManager;


		SysManagerPtr									m_pSysManager;

		Sys_InputPtr									m_pSysInput;

		Sys_GraphicsPtr									m_pSysGraphics;

		boost::shared_ptr<WMInput>						m_pWMInput;
	};


}
