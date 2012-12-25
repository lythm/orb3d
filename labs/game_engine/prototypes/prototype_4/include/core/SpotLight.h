#pragma once
#include "core\Light.h"

namespace engine
{

	class EXPORT_CLASS SpotLight : public Light
	{
	public:
		SpotLight(void);
		virtual ~SpotLight(void);

		const float&					GetAngle();
		void							SetAngle(const float& angle);

	private:
		float							m_angle;
	};

}