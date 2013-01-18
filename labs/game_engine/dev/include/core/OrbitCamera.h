#pragma once

#include "core\Camera.h"


namespace ld3d
{
	class OrbitCamera : public Camera
	{
	public:
		OrbitCamera(void);
		virtual ~OrbitCamera(void);
	};
}
