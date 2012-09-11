#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <xnamath.h>

namespace math
{
	inline
		const Matrix44& Matrix44::operator*=(const Matrix44& rhs)
	{
		XMMATRIX m1 = XMLoadFloat4x4((const XMFLOAT4X4*) this);
		XMMATRIX m2 = XMLoadFloat4x4((const XMFLOAT4X4*) &rhs);

		XMMATRIX r = XMMatrixMultiply(m1, m2);

		XMStoreFloat4x4((XMFLOAT4X4*) this, r);

		return *this;
	}
	inline
		void Matrix44::Transpose()
	{
		XMMATRIX m = XMLoadFloat4x4((const XMFLOAT4X4*)this);

		XMMATRIX r = XMMatrixTranspose(m);

		XMStoreFloat4x4((XMFLOAT4X4*) this, r);

	}
	inline
		void Matrix44::Invert()
	{

		XMMATRIX m = XMLoadFloat4x4((const XMFLOAT4X4*)this);

		XMVECTOR d;
		XMMATRIX r = XMMatrixInverse(&d, m);

		XMStoreFloat4x4((XMFLOAT4X4*) this, r);
	}
	inline
		Vector3 Matrix44::GetScale() const
	{
		XMVECTOR s, r, t;

		XMMATRIX m = XMLoadFloat4x4((const XMFLOAT4X4*)this);

		XMMatrixDecompose(&s, &r, &t, m);


		Vector3 scale;

		XMStoreFloat3((XMFLOAT3*)&scale, s);

		return scale;
	}
	inline
		void Matrix44::SetScale(const Vector3& s)
	{
		XMVECTOR _s, r, t;

		XMMATRIX m = XMLoadFloat4x4((const XMFLOAT4X4*)this);

		XMMatrixDecompose(&_s, &r, &t, m);

		_s = XMLoadFloat3((const XMFLOAT3*)&s);

		m = XMMatrixScalingFromVector(_s) * XMMatrixRotationQuaternion(r) * XMMatrixTranslationFromVector(t);

		XMStoreFloat4x4((XMFLOAT4X4*)this, m);

	}
	inline
		Matrix44 operator*(const Matrix44& lhs, const Matrix44& rhs)
	{


		XMMATRIX m1 = XMLoadFloat4x4((const XMFLOAT4X4*) &lhs);
		XMMATRIX m2 = XMLoadFloat4x4((const XMFLOAT4X4*) &rhs);

		XMMATRIX r = XMMatrixMultiply(m1, m2);

		Matrix44 ret;
		XMStoreFloat4x4((XMFLOAT4X4*) &ret, r);

		return ret;
	}
}

