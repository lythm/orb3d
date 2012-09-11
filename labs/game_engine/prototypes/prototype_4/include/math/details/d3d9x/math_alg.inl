
#include <d3dx9.h>
namespace math
{
	inline
		Vector3 Cross(const Vector3& l, const Vector3& r)
	{
		Vector3 ret;
		D3DXVec3Cross((D3DXVECTOR3*)&ret, (D3DXVECTOR3*)&l, (D3DXVECTOR3*)&r);
		return ret;
	}
	inline
		Vector4 Cross(const Vector4& v1, const Vector4& v2, const Vector4& v3)
	{
		Vector4 ret;
		D3DXVec4Cross((D3DXVECTOR4*)&ret, (D3DXVECTOR4*)&v1, (D3DXVECTOR4*)&v2, (D3DXVECTOR4*)&v3);
		return ret;
	}

	inline
		Matrix44 MatrixRotationAxis(const Vector3& axis, Real rad)
	{
		Matrix44 ret;
		D3DXMatrixRotationAxis((D3DXMATRIX*)&ret, (D3DXVECTOR3*)&axis, rad);
		return ret;
	}
	inline
		Matrix44 MatrixRotationQuat(const Quat& q)
	{
		Matrix44 ret;
		D3DXMatrixRotationQuaternion((D3DXMATRIX*)&ret, (D3DXQUATERNION*)&q);
		return ret;
	}
	inline
		void TransformCoord(Vector2& v, const Matrix44& t)
	{
		D3DXVec2TransformCoord((D3DXVECTOR2*)&v, (D3DXVECTOR2*)&v, (D3DXMATRIX*)&t);
	}
	inline
		void TransformCoord(Vector3& v, const Matrix44& t)
	{
		D3DXVec3TransformCoord((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v, (D3DXMATRIX*)&t);
	}
	inline
		void Transform(Vector4& v, const Matrix44& t)
	{
		D3DXVec4Transform((D3DXVECTOR4*)&v, (D3DXVECTOR4*)&v, (D3DXMATRIX*)&t);
	}
	inline
		void	TransformNormal(Vector2& v, const Matrix44& t)
	{
		D3DXVec2TransformNormal((D3DXVECTOR2*)&v, (D3DXVECTOR2*)&v, (D3DXMATRIX*)&t);
	}
	inline
		void	TransformNormal(Vector3& v, const Matrix44& t)
	{
		D3DXVec3TransformNormal((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v, (D3DXMATRIX*)&t);
	}
	inline
		Matrix44 MatrixLookAtLH(const Vector3& eye, const Vector3& at, const Vector3& up)
	{
		Matrix44 ret;
		D3DXMatrixLookAtLH((D3DXMATRIX*)&ret, (D3DXVECTOR3*)&eye,(D3DXVECTOR3*)&at, (D3DXVECTOR3*)&up);
		return ret;
	}
	inline
		Matrix44 MatrixLookAtRH(const Vector3& eye, const Vector3& at, const Vector3& up)
	{
		Matrix44 ret;
		D3DXMatrixLookAtRH((D3DXMATRIX*)&ret, (D3DXVECTOR3*)&eye,(D3DXVECTOR3*)&at, (D3DXVECTOR3*)&up);
		return ret;
	}
	inline
		Matrix44 MatrixOrthoLH(Real w, Real h, Real zn, Real zf)
	{
		Matrix44 ret;
		D3DXMatrixOrthoLH((D3DXMATRIX*)&ret, w, h, zn, zf);
		return ret;
	}
	inline
		Matrix44 MatrixOrthoRH(Real w, Real h, Real zn, Real zf)
	{
		Matrix44 ret;
		D3DXMatrixOrthoRH((D3DXMATRIX*)&ret, w, h, zn, zf);
		return ret;
	}
	inline
		Matrix44 MatrixPerspectiveLH(Real w, Real h, Real zn, Real zf)
	{
		Matrix44 ret;
		D3DXMatrixPerspectiveLH((D3DXMATRIX*)&ret, w, h, zn, zf);
		return ret;
	}
	inline
		Matrix44 MatrixPerspectiveRH(Real w, Real h, Real zn, Real zf)
	{
		Matrix44 ret;
		D3DXMatrixPerspectiveRH((D3DXMATRIX*)&ret, w, h, zn, zf);
		return ret;
	}
	inline
		Matrix44 MatrixPerspectiveFovLH(Real fov, Real aspect, Real zn, Real zf)
	{
		Matrix44 ret;
		D3DXMatrixPerspectiveFovLH((D3DXMATRIX*)&ret, fov, aspect, zn, zf);
		return ret;
	}
	inline
		Matrix44 MatrixPerspectiveFovRH(Real fov, Real aspect, Real zn, Real zf)
	{
		Matrix44 ret;
		D3DXMatrixPerspectiveFovRH((D3DXMATRIX*)&ret, fov, aspect, zn, zf);
		return ret;
	}
	inline
		Quat Slerp(const Quat& q1, const Quat& q2, Real s)
	{
		Quat ret;
		D3DXQuaternionSlerp((D3DXQUATERNION*)&ret, (D3DXQUATERNION*)&q1, (D3DXQUATERNION*)&q2, s);
		return ret;
	}
	inline
		Quat QuatRotationAxis(const Vector3& axis, Real rad)
	{
		Quat ret;
		D3DXQuaternionRotationAxis((D3DXQUATERNION*)&ret, (D3DXVECTOR3*)&axis, rad);
		return ret;
	}
	inline
		Quat QuatRotationMatrix(const Matrix44& m)
	{
		Quat ret;
		D3DXQuaternionRotationMatrix((D3DXQUATERNION*)&ret, (D3DXMATRIX*)&m);
		return ret;
	}
	inline
		void MatrixDecompose(const Matrix44& m, Vector3& s, Quat& r, Vector3& t)
	{
		D3DXMatrixDecompose((D3DXVECTOR3*)&s, (D3DXQUATERNION*)&r, (D3DXVECTOR3*)&t, (D3DXMATRIX*)&m);
	}
}
