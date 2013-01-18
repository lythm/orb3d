#include "core_pch.h"
#include "core\BaseCamera.h"

namespace ld3d
{
	BaseCamera::BaseCamera(void)
	{
		m_viewMatrix.MakeIdentity();
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
	void BaseCamera::SetViewMatrix(const math::Matrix44& view)
	{
		m_viewMatrix = view;
	}
	void BaseCamera::SetProjMatrix(const math::Matrix44& proj)
	{
		m_projMatrix = proj;
	}

	const ViewFrustum& BaseCamera::GetViewFrustum() const
	{
		return m_frustum;
	}
	void BaseCamera::UpdateViewFrustum()
	{
		m_frustum.Update(m_viewMatrix, m_projMatrix);
	}
	math::Vector3 BaseCamera::GetAxisX()
	{
		return m_viewMatrix.GetCol3(0);
	}
	math::Vector3 BaseCamera::GetAxisY()
	{
		return m_viewMatrix.GetCol3(1);
	}
	math::Vector3 BaseCamera::GetAxisZ()
	{
		return m_viewMatrix.GetCol3(2);
	}
}
