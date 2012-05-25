#include "ede_pch.h"
#include "ede_EventDispatchEngine.h"

namespace orb
{
	namespace ede
	{
		EventDispatchEngine::EventDispatchEngine(void)
		{
		}


		EventDispatchEngine::~EventDispatchEngine(void)
		{
		}

		void EventDispatchEngine::EmmitEvent(Event* e)
		{
			
		}
		
		result EventDispatchEngine::Initialize()
		{
			return ede_ret_ok;
		}
		void EventDispatchEngine::Release()
		{
		}

		result EventDispatchEngine::RegisterEDObject(EDObject* pObj)
		{
			return ede_ret_ok;
		}
		void EventDispatchEngine::UnRegisterEDObject(EDObject* pObj)
		{
		}
	}
}
