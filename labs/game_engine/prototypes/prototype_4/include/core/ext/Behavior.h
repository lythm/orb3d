#pragma once

#include "core\GameObjectComponent.h"

namespace engine
{
	class EXPORT_CLASS Behavior : public GameObjectComponent
	{
	public:
		Behavior(void);
		virtual ~Behavior(void);


		void						Update();
		bool						OnAttach();
		void						OnDetach();

		static BehaviorPtr			CreateComponent();


	};
}
