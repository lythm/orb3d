#pragma once


#include "WinApp.h"
#include "GameManager.h"

namespace ld3d
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

		void											HandleMessage(MSG& msg);
	private:

		
		GameManagerPtr									m_pGameManager;
		CoreApiPtr										m_pCore;
	};


}
