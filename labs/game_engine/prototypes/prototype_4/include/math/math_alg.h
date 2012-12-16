#ifndef __MATH_ALG_H__
#define __MATH_ALG_H__
#pragma once

#ifndef __MATH_TYPES_H__
#include <math/math_types.h>
#endif

#ifndef __MATH_VECTOR2_H__
#include <math/math_vector2.h>
#endif

#ifndef __MATH_VECTOR3_H__
#include <math/math_vector3.h>
#endif

#ifndef __MATH_VECTOR4_H__
#include <math/math_vector4.h>
#endif

#ifndef __MATH_MATRIX44_H__
#include <math/math_matrix44.h>
#endif

#ifndef __MATH_PLANE_H__
#include <math/math_plane.h>
#endif

#ifndef __MATH_QUAT_H__
#include <math/math_quat.h>
#endif

#ifndef __MATH_RAY_H__
#include <math/math_ray.h>
#endif

#ifndef __MATH_AABBOX_H__
#include <math/math_aabbox.h>
#endif

namespace math
{
	Matrix44			MatrixLookAtLH(const Vector3& eye, const Vector3& at, const Vector3& up);
	Matrix44			MatrixLookAtRH(const Vector3& eye, const Vector3& at, const Vector3& up);

	Matrix44			MatrixOrthoLH(Real w, Real h, Real zn, Real zf);
	Matrix44			MatrixOrthoRH(Real w, Real h, Real zn, Real zf);

	Matrix44			MatrixPerspectiveLH(Real w, Real h, Real zn, Real zf);
	Matrix44			MatrixPerspectiveRH(Real w, Real h, Real zn, Real zf);
	Matrix44			MatrixPerspectiveFovLH(Real fov, Real aspect, Real zn, Real zf);
	Matrix44			MatrixPerspectiveFovRH(Real fov, Real aspect, Real zn, Real zf);

	void				MatrixDecompose(const Matrix44& m, Vector3& s, Quat& r, Vector3& t);
	Matrix44			MatrixRotationQuat(const Quat& q);
	Matrix44			MatrixRotationAxis(const Vector3& axis, Real rad);
	Matrix44			MatrixIdentity();
	Matrix44			MatrixRotationRollPitchYaw(float Pitch, float Yaw, float Roll);

	Quat				QuatRotationAxis(const Vector3& axis, Real rad);
	Quat				QuatRotationMatrix(const Matrix44& m);
	Quat				QuatIdentity();
	Quat				QuatRotationRollPitchYaw(float Pitch, float Yaw, float Roll);
		
	void				Transform(Vector4& v, const Matrix44& t);
	void				TransformCoord(Vector2& v, const Matrix44& t);
	void				TransformCoord(Vector3& v, const Matrix44& t);
	void				TransformNormal(Vector2& v, const Matrix44& t);
	void				TransformNormal(Vector3& v, const Matrix44& t);

	Quat				Slerp(const Quat& q1, const Quat& q2, Real s);
	Vector3				Cross(const Vector3& l, const Vector3& r);
	Vector4				Cross(const Vector4& v1, const Vector4& v2, const Vector4& v3);

	bool				TriAABBoxIntersectTest(const Vector3& a, const Vector3& b, const Vector3& c, const AABBox& aabb);

	Ray					UnProject(int x, int y, int vw, int vh, const Matrix44& worldTM, const Matrix44& ViewTM, const Matrix44& ProjTM);
}

// inline declaration
namespace math
{
	template <class T>
	T Lerp(const T& v1, const T& v2, Real s);
	template <class T>
	void Clamp(T& val, const T& minval, const T& maxval);

	template <class T>
	void MinMax(const T& v0, const T& v1, const T& v2, T& max_v, T& min_v);

	Real				D2R(Real degree);
	Real				R2D(Real radian);


	Real				Dot(const Vector2& l, const Vector2& r);
	Real				Dot(const Vector3& l, const Vector3& r);
	Real				Dot(const Vector4& l, const Vector4& r);
	Real				Dot(const Plane& p, const Vector4& v);
	Real				Dot(const Quat& l, Quat& r);
	Real				DotCoord(const Plane& p, const Vector3& v);
	Real				DotNormal(const Plane& p, const Vector3 v);


	Matrix44			MatrixRotationAxisX(Real rad);
	Matrix44			MatrixRotationAxisY(Real rad);
	Matrix44			MatrixRotationAxisZ(Real rad);

	Matrix44			MatrixTranslation(const Vector3& trans);
	Matrix44			MatrixScale(const Vector3& s);
	Matrix44			MatrixTranspose(const Matrix44& m);
	Matrix44			MatrixInverse(const Matrix44& m);


	Quat				QuatRotationAxisX(Real rad);
	Quat				QuatRotationAxisY(Real rad);
	Quat				QuatRotationAxisZ(Real rad);


	template <class T>
	inline 
		T Lerp(const T& v1, const T& v2, Real s)
	{
		return v1 + s * (v2 - v1);
	}
	template <class T>
	inline
		void Clamp(T& val, const T& minval, const T& maxval)
	{
		if(val < minval)
			val = minval;
		if(val > maxval)
			val = maxval;
	}
	inline
	Real D2R(Real degree)
	{
		return degree / 180.0f * MATH_PI;
	}
	inline
	Real R2D(Real radian)
	{
		return radian / MATH_PI * 180.0f;
	}
	inline
		Real Dot(const Vector2& l, const Vector2& r)
	{
		return l.x * r.x + l.y * r.y;
	}

	inline
		Real Dot(const Vector3& l, const Vector3& r)
	{
		return l.x * r.x + l.y * r.y + l.z * r.z;
	}

	inline
		Real Dot(const Vector4& l, const Vector4& r)
	{
		return l.x * r.x + l.y * r.y + l.z * r.z + l.w * r.w;
	}
	inline
		Real Dot(const Quat& l, Quat& r)
	{
		return l.x * r.x + l.y * r.y + l.z * r.z + l.w * r.w;
	}
	inline
		Real Dot(const Plane& p, const Vector4& v)
	{
		return p.a * v.x + p.b * v.y + p.c * v.z + p.d * v.w;
	}

	inline
		Real DotCoord(const Plane& p, const Vector3& v)
	{
		return p.a * v.x + p.b * v.y + p.c * v.z + p.d;
	}
	inline
		Real DotNormal(const Plane& p, const Vector3 v)
	{
		return p.a * v.x + p.b * v.y + p.c * v.z;
	}

	inline
		Matrix44 MatrixRotationAxisX(Real rad)
	{
		return MatrixRotationAxis(Vector3(1, 0, 0), rad);
	}
	inline
		Matrix44 MatrixRotationAxisY(Real rad)
	{
		return MatrixRotationAxis(Vector3(0, 1, 0), rad);
	}
	inline
		Matrix44 MatrixRotationAxisZ(Real rad)
	{
		return MatrixRotationAxis(Vector3(0, 0, 1), rad);
	}
	inline
		Matrix44 MatrixTranspose(const Matrix44& m)
	{
		Matrix44 ret = m;
		ret.Transpose();
		return ret;
	}
	inline
		Matrix44 MatrixInverse(const Matrix44& m)
	{
		Matrix44 ret = m;
		ret.Invert();
		return ret;
	}
	inline
		Matrix44 MatrixTranslation(const Vector3& trans)
	{
		Matrix44 ret;
		ret.MakeIdentity();
		ret.SetRow3(3, trans);
		return ret;
	}
	inline
		Matrix44 MatrixScale(const Vector3& s)
	{
		Matrix44 ret;
		ret.MakeIdentity();
		ret(0, 0) = s.x;
		ret(1, 1) = s.y;
		ret(2, 2) = s.z;
		return ret;
	}
	inline
		Matrix44 MatrixIdentity()
	{
		Matrix44 ret;
		ret.MakeIdentity();
		return ret;
	}

	inline
		Quat QuatIdentity()
	{
		Quat q;
		q.MakeIdentity();
		return q;
	}
	inline
		Quat QuatRotationAxisX(Real rad)
	{
		return QuatRotationAxis(Vector3(1, 0, 0), rad);
	}
	inline
		Quat QuatRotationAxisY(Real rad)
	{
		return QuatRotationAxis(Vector3(0, 1, 0), rad);
	}
	inline
		Quat QuatRotationAxisZ(Real rad)
	{
		return QuatRotationAxis(Vector3(0, 0, 1), rad);
	}


	template <class T>
	inline
		void MinMax(const T& v0, const T& v1, const T& v2, T& max_v, T& min_v)
	{
		max_v = min_v = v0;
		if(v1 < min_v)	min_v = v1;
		if(v1 > max_v)	max_v = v1;

		if(v2 < min_v)	min_v = v2;
		if(v2 > max_v)	max_v = v2;
	}

}

#ifdef _D3DX9_IMPL_
#include <math/details/d3d9x/math_alg.inl>
#endif

#ifdef _XNAMATH_IMPL_
#include <math/details/xnamath/math_alg.inl>
#endif



#endif