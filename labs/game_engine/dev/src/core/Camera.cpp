#include "core_pch.h"
#include "..\..\include\core\Camera.h"


namespace ld3d
{

	Camera::Camera(void)
	{
		m_order = 0;
	}


	Camera::~Camera(void)
	{
	}
	void Camera::SetOrder(const int& order)
	{
		m_order = order;
	}
	const int& Camera::GetOrder()
	{
		return m_order;
	}
	bool Camera::SortFunction(CameraPtr pC1, CameraPtr pC2)
	{
		return pC1->GetOrder() <= pC2->GetOrder();
	}
}
