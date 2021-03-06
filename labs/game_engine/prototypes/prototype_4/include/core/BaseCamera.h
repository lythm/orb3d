#pragma once
#include "core\ViewFrustum.h"

namespace engine
{
	class EXPORT_CLASS BaseCamera
	{
	public:
		BaseCamera(void);
		virtual ~BaseCamera(void);


		void													LookAtLH(const math::Vector3& eye, const math::Vector3 at, const math::Vector3& up);
		void													LookAtRH(const math::Vector3& eye, const math::Vector3 at, const math::Vector3& up);

		void													PerspectiveFovLH(Real fov, Real aspect, Real zn, Real zf);
		void													PerspectiveFovRH(Real fov, Real aspect, Real zn, Real zf);

		virtual const math::Matrix44&							GetViewMatrix() const;
		virtual const math::Matrix44&							GetProjMatrix() const;

		void													SetViewMatrix(const math::Matrix44& view);
		void													SetProjMatrix(const math::Matrix44& proj);

		const ViewFrustum&										GetViewFrustum() const;
		void													UpdateViewFrustum();

	private:
		math::Matrix44											m_viewMatrix;
		math::Matrix44											m_projMatrix;

		ViewFrustum												m_frustum;
	};
}

