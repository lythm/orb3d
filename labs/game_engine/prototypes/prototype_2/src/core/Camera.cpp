#include "core_pch.h"
#include "core\Camera.h"

namespace engine
{
	Camera::Camera(void)
	{

		m_viewMatrix.SetIdentity();

	}


	Camera::~Camera(void)
	{
	}
	const math::Matrix44& Camera::GetViewMatrix() const
	{
		return m_viewMatrix;
	}
	const math::Matrix44& Camera::GetProjMatrix() const
	{
		return m_projMatrix;
	}
	void Camera::Update()
	{

	}
	void Camera::LookAtLH(const math::Vector3& eye, const math::Vector3 at, const math::Vector3& up)
	{
		m_viewMatrix = math::MatrixLookAtLH(eye, at, up);
	}
	void Camera::LookAtRH(const math::Vector3& eye, const math::Vector3 at, const math::Vector3& up)
	{
		m_viewMatrix = math::MatrixLookAtRH(eye, at, up);
	}
	void Camera::PerspectiveFovLH(Real fov, Real aspect, Real zn, Real zf)
	{
		m_projMatrix = math::MatrixPerspectiveFovLH(fov, aspect, zn, zf);
	}
	void Camera::PerspectiveFovRH(Real fov, Real aspect, Real zn, Real zf)
	{
		m_projMatrix = math::MatrixPerspectiveFovRH(fov, aspect, zn, zf);
	}
}
