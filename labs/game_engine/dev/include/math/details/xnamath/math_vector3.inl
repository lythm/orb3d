#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <xnamath.h>


namespace math
{

	inline
		void Vector3::Normalize()
	{

		XMVECTOR val = XMLoadFloat3((const XMFLOAT3*)this);

		XMVECTOR r = XMVector3Normalize(val);

		XMStoreFloat3((XMFLOAT3*)this, r);

	}

}