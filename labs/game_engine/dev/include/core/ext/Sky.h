#pragma once

#include "core\GameObjectComponent.h"

namespace engine
{
	class Sky : public GameObjectComponent
	{
	public:
		Sky(GameObjectManagerPtr pManager);
		virtual ~Sky(void);

	private:
		bool										OnAttach();
		void										OnDetach();

	};


}