#pragma once

namespace ld3d
{
	class EXPORT_CLASS ArcBall
	{
	public:
		ArcBall(void);
		virtual ~ArcBall(void);

		void							SetViewPort(int w, int h, float radius = 0.9f);
		
		void							Begin(int x, int y);
		void							Move(int x, int y);
		void							End();

		void							Reset();
		// screen point to clipping space vector
		math::Vector3					ScreenToVector(float screen_x, float screen_y);
		math::Quat						QuatFromVector(const math::Vector3& from, const math::Vector3& to);
		math::Matrix44					GetRotationMatrix();
		const math::Quat&				GetRotationQuat();
	private:
		int								m_screenWidth;
		int								m_screenHeight;
		math::Vector3					m_center;
		float							m_radius;


		math::Matrix44					m_rotationMatrix;
		math::Quat						m_startQuat;
		math::Quat						m_currentQuat;
		bool							m_bDrag;

		math::Vector3					m_startPoint;
		math::Vector3					m_currentPoint;

	};


}