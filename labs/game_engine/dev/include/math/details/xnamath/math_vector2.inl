#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <xnamath.h>

namespace math
{
	inline
		void Vector2::Normalize()
	{
		
		XMVECTOR v = XMLoadFloat2((const XMFLOAT2*)this);

		XMVECTOR r = XMVector2Normalize(v);

		XMStoreFloat2((XMFLOAT2*)this, r);
	}
}
