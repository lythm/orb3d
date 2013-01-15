#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <xnamath.h>
namespace math
{
	inline
		Vector3 Cross(const Vector3& l, const Vector3& r)
	{
		XMVECTOR v1 = XMLoadFloat3((const XMFLOAT3*)&l);
		XMVECTOR v2 = XMLoadFloat3((const XMFLOAT3*)&r);

		XMVECTOR _r = XMVector3Cross(v1, v2);

		Vector3 ret;

		XMStoreFloat3((XMFLOAT3*)&ret, _r);

		return ret;
	}
	inline
		Vector4 Cross(const Vector4& v1, const Vector4& v2, const Vector4& v3)
	{

		XMVECTOR _v1 = XMLoadFloat4((const XMFLOAT4*)&v1);
		XMVECTOR _v2 = XMLoadFloat4((const XMFLOAT4*)&v2);
		XMVECTOR _v3 = XMLoadFloat4((const XMFLOAT4*)&v3);

		XMVECTOR r = XMVector4Cross(_v1, _v2, _v3);

		Vector4 ret;

		XMStoreFloat4((XMFLOAT4*)&ret, r);

		return ret;
	}

	inline
		Matrix44 MatrixRotationAxis(const Vector3& axis, Real rad)
	{
		Matrix44 ret;

		XMVECTOR _axis = XMLoadFloat3((const XMFLOAT3*)&axis);

		XMMATRIX r = XMMatrixRotationAxis(_axis, rad);

		XMStoreFloat4x4((XMFLOAT4X4*)&ret, r);

		return ret;
	}
	inline
		Matrix44 MatrixRotationQuat(const Quat& q)
	{
		Matrix44 ret;

		XMVECTOR _q = XMLoadFloat4((const XMFLOAT4*)&q);

		XMMATRIX r = XMMatrixRotationQuaternion(_q);

		XMStoreFloat4x4((XMFLOAT4X4*)&ret, r);

		return ret;
	}
	inline
		void TransformCoord(Vector2& v, const Matrix44& t)
	{
		XMVECTOR _v = XMLoadFloat2((const XMFLOAT2*)&v);

		XMMATRIX _t = XMLoadFloat4x4((const XMFLOAT4X4*)&t);

		XMVECTOR r = XMVector2TransformCoord(_v, _t);

		XMStoreFloat2((XMFLOAT2*)&v, r);
	}
	inline
		void TransformCoord(Vector3& v, const Matrix44& t)
	{

		XMVECTOR _v = XMLoadFloat3((const XMFLOAT3*)&v);

		XMMATRIX _t = XMLoadFloat4x4((const XMFLOAT4X4*)&t);

		XMVECTOR r = XMVector3TransformCoord(_v, _t);

		XMStoreFloat3((XMFLOAT3*)&v, r);

	}
	inline
		void Transform(Vector4& v, const Matrix44& t)
	{

		XMVECTOR _v = XMLoadFloat4((const XMFLOAT4*)&v);

		XMMATRIX _t = XMLoadFloat4x4((const XMFLOAT4X4*)&t);

		XMVECTOR r = XMVector4Transform(_v, _t);

		XMStoreFloat4((XMFLOAT4*)&v, r);

	}
	inline
		void TransformNormal(Vector2& v, const Matrix44& t)
	{
		XMVECTOR _v = XMLoadFloat2((const XMFLOAT2*)&v);

		XMMATRIX _t = XMLoadFloat4x4((const XMFLOAT4X4*)&t);

		XMVECTOR r = XMVector2TransformNormal(_v, _t);

		XMStoreFloat2((XMFLOAT2*)&v, r);
	}
	inline
		void	TransformNormal(Vector3& v, const Matrix44& t)
	{
		XMVECTOR _v = XMLoadFloat3((const XMFLOAT3*)&v);

		XMMATRIX _t = XMLoadFloat4x4((const XMFLOAT4X4*)&t);

		XMVECTOR r = XMVector3TransformNormal(_v, _t);

		XMStoreFloat3((XMFLOAT3*)&v, r);
	}
	inline
		Matrix44 MatrixLookAtLH(const Vector3& eye, const Vector3& at, const Vector3& up)
	{
		Matrix44 ret;

		XMVECTOR _eye = XMLoadFloat3((const XMFLOAT3*)&eye);
		XMVECTOR _at = XMLoadFloat3((const XMFLOAT3*)&at);
		XMVECTOR _up = XMLoadFloat3((const XMFLOAT3*)&up);

		XMMATRIX r = XMMatrixLookAtLH(_eye, _at, _up);

		XMStoreFloat4x4((XMFLOAT4X4*)&ret, r);
		return ret;
	}
	inline
		Matrix44 MatrixLookAtRH(const Vector3& eye, const Vector3& at, const Vector3& up)
	{
		Matrix44 ret;

		XMVECTOR _eye = XMLoadFloat3((const XMFLOAT3*)&eye);
		XMVECTOR _at = XMLoadFloat3((const XMFLOAT3*)&at);
		XMVECTOR _up = XMLoadFloat3((const XMFLOAT3*)&up);

		XMMATRIX r = XMMatrixLookAtRH(_eye, _at, _up);

		XMStoreFloat4x4((XMFLOAT4X4*)&ret, r);
		return ret;
	}
	inline
		Matrix44 MatrixOrthoLH(Real w, Real h, Real zn, Real zf)
	{
		Matrix44 ret;

		XMMATRIX r = XMMatrixOrthographicLH(w, h, zn, zf);
		XMStoreFloat4x4((XMFLOAT4X4*)&ret, r);

		return ret;
	}
	inline
		Matrix44 MatrixOrthoRH(Real w, Real h, Real zn, Real zf)
	{
		Matrix44 ret;

		XMMATRIX r = XMMatrixOrthographicRH(w, h, zn, zf);
		XMStoreFloat4x4((XMFLOAT4X4*)&ret, r);

		return ret;
	}
	inline
		Matrix44 MatrixPerspectiveLH(Real w, Real h, Real zn, Real zf)
	{
		Matrix44 ret;

		XMMATRIX r = XMMatrixPerspectiveLH(w, h, zn, zf);
		XMStoreFloat4x4((XMFLOAT4X4*)&ret, r);

		return ret;
	}
	inline
		Matrix44 MatrixPerspectiveRH(Real w, Real h, Real zn, Real zf)
	{
		Matrix44 ret;

		XMMATRIX r = XMMatrixPerspectiveRH(w, h, zn, zf);
		XMStoreFloat4x4((XMFLOAT4X4*)&ret, r);

		return ret;
	}
	inline
		Matrix44 MatrixPerspectiveFovLH(Real fov, Real aspect, Real zn, Real zf)
	{
		Matrix44 ret;

		XMMATRIX r = XMMatrixPerspectiveFovLH(fov, aspect, zn, zf);
		XMStoreFloat4x4((XMFLOAT4X4*)&ret, r);

		return ret;
	}
	inline
		Matrix44 MatrixPerspectiveFovRH(Real fov, Real aspect, Real zn, Real zf)
	{
		Matrix44 ret;

		XMMATRIX r = XMMatrixPerspectiveFovRH(fov, aspect, zn, zf);
		XMStoreFloat4x4((XMFLOAT4X4*)&ret, r);

		return ret;
	}
	inline
		Matrix44 MatrixRotationRollPitchYaw(float Pitch, float Yaw, float Roll)
	{
		XMMATRIX r = XMMatrixRotationRollPitchYaw(Pitch, Yaw, Roll);
		Matrix44 ret;
		XMStoreFloat4x4((XMFLOAT4X4*)&ret, r);

		return ret;
	}
	inline
		Quat Slerp(const Quat& q1, const Quat& q2, Real s)
	{
		Quat ret;

		XMVECTOR _q1 = XMLoadFloat4((const XMFLOAT4*)&q1);
		XMVECTOR _q2 = XMLoadFloat4((const XMFLOAT4*)&q2);


		XMVECTOR r = XMQuaternionSlerp(_q1, _q2, s);

		XMStoreFloat4((XMFLOAT4*)&ret, r);
		return ret;
	}
	inline
		Quat QuatRotationAxis(const Vector3& axis, Real rad)
	{
		Quat ret;

		XMVECTOR _axis = XMLoadFloat3((const XMFLOAT3*)&axis);

		XMVECTOR r = XMQuaternionRotationAxis(_axis, rad);
		XMStoreFloat4((XMFLOAT4*)&ret, r);
		return ret;
	}
	inline
		Quat QuatRotationMatrix(const Matrix44& m)
	{
		Quat ret;

		XMMATRIX _m = XMLoadFloat4x4((const XMFLOAT4X4*)&m);

		XMVECTOR r = XMQuaternionRotationMatrix(_m);
		XMStoreFloat4((XMFLOAT4*)&ret, r);
		return ret;
	}
	inline
		Quat QuatRotationRollPitchYaw(float Pitch, float Yaw, float Roll)
	{
		Quat ret;

		XMVECTOR r = XMQuaternionRotationRollPitchYaw(Pitch, Yaw, Roll);
		XMStoreFloat4((XMFLOAT4*)&ret, r);
		return ret;
	}
	inline
		void MatrixDecompose(const Matrix44& m, Vector3& s, Quat& r, Vector3& t)
	{
		XMMATRIX _m = XMLoadFloat4x4((const XMFLOAT4X4*)&m);

		XMVECTOR _s , _t, _r;
		XMMatrixDecompose(&_s, &_r, &_t, _m);

		XMStoreFloat3((XMFLOAT3*)&s, _s);
		XMStoreFloat3((XMFLOAT3*)&t, _t);

		XMStoreFloat4((XMFLOAT4*)&r, _r);
	}

	inline
		Ray	UnProject(int x, int y, int vw, int vh, const Matrix44& worldTM, const Matrix44& ViewTM, const Matrix44& ProjTM)
	{
		Vector3 v;
		v.x = -( ( ( 2.0f * x ) / vw  ) - 1 ) / ProjTM(0,0);
		v.y = ( ( ( 2.0f * y ) / vh ) - 1 ) / ProjTM(1,1);
		v.z =  -1.0f;


		math::Matrix44 m = worldTM * ViewTM;
		m.Invert();

		Ray r;
		// Transform the screen space pick ray into 3D space
		r.d.x  = -(v.x*m(0,0) + v.y*m(1,0) + v.z*m(2,0));
		r.d.y  = -(v.x*m(0,1) + v.y*m(1,1) + v.z*m(2,1));
		r.d.z  = -(v.x*m(0,2) + v.y*m(1,2) + v.z*m(2,2));
		r.o.x = m(3,0);
		r.o.y = m(3,1);
		r.o.z = m(3,2);

		return r;
	}
}
