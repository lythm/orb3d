#pragma once

#include "core\GameObjectComponent.h"


namespace engine
{
	class MeshRenderer : public GameObjectComponent
	{
	public:
		MeshRenderer(void);
		virtual ~MeshRenderer(void);

		void							Update();
	};


}
