#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <xnamath.h>
namespace math
{
	inline
		void Quat::Invert()
	{

		XMVECTOR q = XMLoadFloat4((const XMFLOAT4*)this);

		XMVECTOR r = XMQuaternionInverse(q);

		XMStoreFloat4((XMFLOAT4*)this, r);
	}
	inline
		const Quat& Quat::operator*=(const Quat& rhs)
	{
		XMVECTOR q1 = XMLoadFloat4((const XMFLOAT4*)this);
		XMVECTOR q2 = XMLoadFloat4((const XMFLOAT4*)&rhs);

		XMVECTOR r = XMQuaternionMultiply(q1, q2);

		XMStoreFloat4((XMFLOAT4*)this, r);

		return *this;
	}
	inline
		void Quat::Normalize()
	{

		XMVECTOR q = XMLoadFloat4((const XMFLOAT4*)this);

		XMVECTOR r = XMQuaternionNormalize(q);

		XMStoreFloat4((XMFLOAT4*)this, r);
	}
}