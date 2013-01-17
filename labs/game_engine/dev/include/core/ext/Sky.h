#pragma once

#include "core\GameObjectComponent.h"

namespace ld3d
{
	class Sky : public GameObjectComponent
	{
	public:
		Sky(GameObjectManagerPtr pManager);
		virtual ~Sky(void);

		const Version&								GetVersion() const;

	private:
		bool										OnAttach();
		void										OnDetach();

	};


}