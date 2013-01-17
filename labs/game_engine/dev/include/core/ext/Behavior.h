#pragma once

#include "core\GameObjectComponent.h"

namespace ld3d
{
	class EXPORT_CLASS Behavior : public GameObjectComponent
	{
	public:
		Behavior(GameObjectManagerPtr pManager);
		virtual ~Behavior(void);


		void						Update();
		bool						OnAttach();
		void						OnDetach();

		const Version&				GetVersion() const;

	};
}
