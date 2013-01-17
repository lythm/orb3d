#pragma once

#include "core\GameObjectComponent.h"

namespace ld3d
{
	class SkyBox : public GameObjectComponent
	{
	public:
		SkyBox(GameObjectManagerPtr pManager);
		virtual ~SkyBox(void);

		void										Update();
		const Version&								GetVersion() const;
	private:
		bool										OnAttach();
		void										OnDetach();
	private:

	};


}