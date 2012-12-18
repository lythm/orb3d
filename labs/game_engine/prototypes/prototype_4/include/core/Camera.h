#pragma once

#include "core\BaseCamera.h"
namespace engine
{

	class EXPORT_CLASS Camera : public BaseCamera
	{
	public:
		Camera(void);
		virtual ~Camera(void);


	private:
		std::vector<PostProcessPtr>					m_pps;
	};
}
