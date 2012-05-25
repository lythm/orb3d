#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <xnamath.h>


namespace math
{

	inline
		void Vector3::Normalize()
	{

		XMVECTOR v = XMLoadFloat3((const XMFLOAT3*)this);

		XMVECTOR r = XMVector3Normalize(v);

		XMStoreFloat3((XMFLOAT3*)this, r);

	}

}