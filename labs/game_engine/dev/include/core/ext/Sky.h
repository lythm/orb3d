#pragma once

#include "core\GameObjectComponent.h"

namespace ld3d
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