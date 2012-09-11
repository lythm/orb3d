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

		GameObjectManagerPtr							m_pObjectManager;

	};


}