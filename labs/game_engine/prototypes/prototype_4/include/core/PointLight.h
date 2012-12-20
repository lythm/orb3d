#pragma once
#include "core\Light.h"

namespace engine
{
	class EXPORT_CLASS PointLight : public Light
	{
	public:
		PointLight(void);
		virtual ~PointLight(void);

		float					GetRadius();
		void					SetRadius(float r);

		float					GetFallout();
		void					SetFallout(float f);

	private:
		float					m_radius;
		float					m_fallout;
	};
}
