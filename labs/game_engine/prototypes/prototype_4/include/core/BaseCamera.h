#pragma once

namespace engine
{
	class BaseCamera
	{
	public:
		BaseCamera(void);
		virtual ~BaseCamera(void);


		void													LookAtLH(const math::Vector3& eye, const math::Vector3 at, const math::Vector3& up);
		void													LookAtRH(const math::Vector3& eye, const math::Vector3 at, const math::Vector3& up);

		void													PerspectiveFovLH(Real fov, Real aspect, Real zn, Real zf);
		void													PerspectiveFovRH(Real fov, Real aspect, Real zn, Real zf);

		virtual void											Update();
		virtual const math::Matrix44&							GetViewMatrix() const;
		virtual const math::Matrix44&							GetProjMatrix() const;

	private:
		math::Matrix44											m_viewMatrix;
		math::Matrix44											m_projMatrix;
	};
}

