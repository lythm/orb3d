#pragma once

#include "ede_event.h"
#include "ede_ret.h"
#include <vector>
#include <map>


namespace orb
{
	namespace ede
	{
		class EventListener;
		class EDObject;

		class _DLL_CLASS EventDispatchEngine
		{
		public:
			struct EDObjectAgent
			{
				EDObjectId					id;
				EDObject*					obj;

				std::list<EDObjectId>		clients;
			};
			
			EventDispatchEngine(void);
			virtual ~EventDispatchEngine(void);

			result														RegisterEDObject(EDObject* pObj);
			void														UnRegisterEDObject(EDObject* pObj);
			

			result														Initialize();
			void														Release();

			void														EmmitEvent(Event* e);

		private:

			std::vector<EDObject*>										m_EDObjects;

		};
	}
}
