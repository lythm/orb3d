#include "core_pch.h"
#include "core\BaseCamera.h"

namespace engine
{
	BaseCamera::BaseCamera(void)
	{

		m_viewMatrix.SetIdentity();

	}


	BaseCamera::~BaseCamera(void)
	{
	}
	const math::Matrix44& BaseCamera::GetViewMatrix() const
	{
		return m_viewMatrix;
	}
	const math::Matrix44& BaseCamera::GetProjMatrix() const
	{
		return m_projMatrix;
	}
	void BaseCamera::Update()
	{

	}
	void BaseCamera::LookAtLH(const math::Vector3& eye, const math::Vector3 at, const math::Vector3& up)
	{
		m_viewMatrix = math::MatrixLookAtLH(eye, at, up);
	}
	void BaseCamera::LookAtRH(const math::Vector3& eye, const math::Vector3 at, const math::Vector3& up)
	{
		m_viewMatrix = math::MatrixLookAtRH(eye, at, up);
	}
	void BaseCamera::PerspectiveFovLH(Real fov, Real aspect, Real zn, Real zf)
	{
		m_projMatrix = math::MatrixPerspectiveFovLH(fov, aspect, zn, zf);
	}
	void BaseCamera::PerspectiveFovRH(Real fov, Real aspect, Real zn, Real zf)
	{
		m_projMatrix = math::MatrixPerspectiveFovRH(fov, aspect, zn, zf);
	}
}
