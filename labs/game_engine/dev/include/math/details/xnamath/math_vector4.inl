#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <xnamath.h>
namespace math
{
	inline
		void Vector4::Normalize()
	{

		XMVECTOR v = XMLoadFloat4((const XMFLOAT4*)this);

		XMVECTOR r = XMVector4Normalize(v);

		XMStoreFloat4((XMFLOAT4*)this, r);

	}


}