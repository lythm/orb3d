#pragma once

#include "core\GameObjectComponent.h"

namespace engine
{
	class EXPORT_CLASS Behavior : public GameObjectComponent
	{
	public:
		Behavior(GameObjectManagerPtr pManager);
		virtual ~Behavior(void);


		void						Update();
		bool						OnAttach();
		void						OnDetach();

	};
}
