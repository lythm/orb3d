#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <xnamath.h>

namespace math
{
	inline	
		Plane::Plane(const Vector3& n, const Vector3& p)
	{
		XMVECTOR xmp = XMLoadFloat3((const XMFLOAT3*)&p);
		XMVECTOR xmn = XMLoadFloat3((const XMFLOAT3*)&n);

		XMVECTOR r = XMPlaneFromPointNormal(xmp, xmn);

		XMStoreFloat4((XMFLOAT4*) this, r);
	}
	inline
		Plane::Plane(const Vector3& p1, const Vector3& p2, const Vector3& p3)
	{
		XMVECTOR _p1 = XMLoadFloat3((const XMFLOAT3*)&p1);
		XMVECTOR _p2 = XMLoadFloat3((const XMFLOAT3*)&p2);
		XMVECTOR _p3 = XMLoadFloat3((const XMFLOAT3*)&p3);

		XMVECTOR r = XMPlaneFromPoints(_p1, _p2, _p3);

		XMStoreFloat4((XMFLOAT4*) this, r);
	}
	inline
		void Plane::Normalize()
	{
		XMVECTOR p = XMLoadFloat4((const XMFLOAT4*)this);

		XMVECTOR r = XMPlaneNormalize(p);

		XMStoreFloat4((XMFLOAT4*) this, r);
	}
}
