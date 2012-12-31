#pragma once

#include "core\GameObjectComponent.h"

namespace engine
{
	class SkyBox : public GameObjectComponent
	{
	public:
		SkyBox(GameObjectManagerPtr pManager);
		virtual ~SkyBox(void);

		void										Update();

	private:
		bool										OnAttach();
		void										OnDetach();
	private:

	};


}