#include "core_pch.h"
#include "..\..\include\core\ArcBall.h"

namespace ld3d
{
	ArcBall::ArcBall(void)
	{
		m_screenWidth			= 800;
		m_screenHeight			= 600;
		m_radius				= 0.9f;
		Reset();
	}


	ArcBall::~ArcBall(void)
	{
	}
	void ArcBall::Reset()
	{
		using namespace math;
		m_bDrag					= false;
		m_rotationMatrix.MakeIdentity();
		m_startQuat.MakeIdentity();
		m_currentQuat.MakeIdentity();


		m_startPoint			= Vector3();
		m_currentPoint			= Vector3();
	}
	void ArcBall::SetViewPort(int w, int h, float radius)
	{
		m_screenWidth = w;
		m_screenHeight = h;
		m_radius = radius;

		m_center.x = w / 2.0f;
		m_center.y = h / 2.0f;
	}

	math::Vector3 ArcBall::ScreenToVector(float screen_x, float screen_y)
	{
		using namespace math;

		// Scale to screen
		float x = -( screen_x - m_screenWidth / 2 ) / ( m_radius * m_screenWidth / 2 );
		float y = ( screen_y - m_screenHeight / 2 ) / ( m_radius * m_screenHeight / 2 );

		float z = 0.0f;
		float mag = x * x + y * y;

		if( mag > 1.0f )
		{
			float scale = 1.0f / sqrtf( mag );
			x *= scale;
			y *= scale;
		}
		else
			z = sqrtf( 1.0f - mag );

		Vector3 v(x, y, z);
		v.Normalize();

		return v;

	}

	void ArcBall::Begin(int x, int y)
	{
		if( x >= 0 && x < m_screenWidth &&
			y >= 0 && y < m_screenHeight)
		{
			m_bDrag = true;
			m_startQuat = m_currentQuat;
			m_startPoint = ScreenToVector( ( float )x, ( float )y );
		}
	}
	void ArcBall::Move(int x, int y)
	{
		if( m_bDrag )
		{
			m_currentPoint = ScreenToVector( ( float )x, ( float )y );
			m_currentQuat = m_startQuat * QuatFromVector( m_startPoint, m_currentPoint);
		}
	}
	void ArcBall::End()
	{
		m_bDrag = false;
	}

	math::Quat ArcBall::QuatFromVector(const math::Vector3& from, const math::Vector3& to)
	{
		using namespace math;

		
		Vector3 vCross;
		float dot = Dot(from, to);
		vCross = Cross(from, to);

		Quat q (vCross.x, vCross.y, vCross.z, dot);
		return q;

		
	}
	math::Matrix44 ArcBall::GetRotationMatrix()
	{
		using namespace math;

		return MatrixRotationQuat(m_currentQuat);
	}
	const math::Quat& ArcBall::GetRotationQuat()
	{
		return m_currentQuat;
	}
}
