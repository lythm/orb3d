#include <d3dx9.h>
namespace math
{
	inline
		const Matrix44& Matrix44::operator*=(const Matrix44& rhs)
	{
		D3DXMatrixMultiply((D3DXMATRIX*)this,  (D3DXMATRIX*)this, (D3DXMATRIX*)&rhs);
		return *this;
	}
	inline
		void Matrix44::Transpose()
	{
		D3DXMatrixTranspose((D3DXMATRIX*)this, (D3DXMATRIX*)this);
	}
	inline
		void Matrix44::Invert()
	{
		D3DXMatrixInverse((D3DXMATRIX*)this, NULL, (D3DXMATRIX*)this);
	}
	inline
		Vector3 Matrix44::GetScale() const
	{
		Vector3 scale, trans;
		D3DXQUATERNION rot;

		D3DXMatrixDecompose((D3DXVECTOR3*)&scale, (D3DXQUATERNION*)&rot, (D3DXVECTOR3*)&trans, (D3DXMATRIX*)this);

		return scale;
	}
	inline
		void Matrix44::SetScale(const Vector3& s)
	{
		Vector3 _s, t;
		D3DXQUATERNION r;

		D3DXMatrixDecompose((D3DXVECTOR3*)&_s, (D3DXQUATERNION*)&r, (D3DXVECTOR3*)&t, (const D3DXMATRIX*) this);

		Matrix44 m1, m2, m3;

		D3DXMatrixScaling((D3DXMATRIX*)&m1, s.x, s.y, s.z);

		D3DXMatrixRotationQuaternion((D3DXMATRIX*)&m2, &r);

		D3DXMatrixTranslation((D3DXMATRIX*)&m3, t.x, t.y, t.z);

		*this = m1 * m2 * m3;

	}

	inline
		Matrix44 operator*(const Matrix44& lhs, const Matrix44& rhs)
	{
		Matrix44 ret;
		D3DXMatrixMultiply((D3DXMATRIX*)&ret,  (D3DXMATRIX*)&lhs, (D3DXMATRIX*)&rhs);
		return ret;
	}
}

