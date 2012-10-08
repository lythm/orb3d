#ifndef __MATH_MATRIX44_H__
#define __MATH_MATRIX44_H__
#pragma once

#ifndef __MATH_TYPES_H__
#include <math/math_types.h>
#endif

#ifndef __MATH_VECTOR3_H__
#include <math/math_vector3.h>
#endif

#ifndef __MATH_VECTOR4_H__
#include <math/math_vector4.h>
#endif

namespace math
{
	class Matrix44
	{
	public:
		Matrix44(void);
		Matrix44(Real _m11, Real _m12, Real _m13, Real _m14,
			Real _m21, Real _m22, Real _m23, Real _m24,
			Real _m31, Real _m32, Real _m33, Real _m34,
			Real _m41, Real _m42, Real _m43, Real _m44);

		~Matrix44(void);

		Real&					operator()(int i, int j);
		const Real&				operator()(int i, int j) const;

		const Matrix44&			operator*=(Real s);
		const Matrix44&			operator/=(Real s);

		const Matrix44&			operator+=(const Matrix44& rhs);
		const Matrix44&			operator-=(const Matrix44& rhs);
		const Matrix44&			operator*=(const Matrix44& rhs);

		Matrix44				operator-()const;
		Matrix44				operator+()const;

		Vector3					GetScale() const;
		Vector3					GetTranslation() const;
		Vector3					GetRow3(int row) const;
		Vector3					GetCol3(int col) const;
		Vector4					GetRow4(int row) const;
		Vector4					GetCol4(int col) const;

		void					SetRow3(int row, const Vector3& val);
		void					SetRow4(int row, const Vector4& val);
		void					SetCol3(int col, const Vector3& val);
		void					SetCol4(int col, const Vector4& val);
		void					SetTranslation(const Vector3& trans);
		void					SetScale(const Vector3& s);

		bool					IsIdentity() const;
		void					MakeIdentity();
		void					Transpose();
		void					Invert();

		union
		{
			struct
			{
				Real	m11, m12, m13, m14,
					m21, m22, m23, m24,
					m31, m32, m33, m34,
					m41, m42, m43, m44;
			};
			Real	m[16];
		};
	};

	inline
		Vector3 Matrix44::GetTranslation() const
	{
		return GetRow3(3);
	}
	inline
		void Matrix44::SetTranslation(const Vector3& trans)
	{
		SetRow3(3, trans);
	}
	inline
		void Matrix44::SetCol3(int col, const Vector3& val)
	{
		m[col]			= val.x;
		m[col + 4]		= val.y;
		m[col + 8]		= val.z;
	}
	inline
		Vector3 Matrix44::GetCol3(int col) const
	{
		return Vector3(m[col], m[col + 4], m[col + 8]);
	}
	inline
		void Matrix44::SetCol4(int col, const Vector4& val)
	{
		m[col]			= val.x;
		m[col + 4]		= val.y;
		m[col + 8]		= val.z;
		m[col + 12]		= val.w;

	}
	inline
		Vector4 Matrix44::GetCol4(int col) const
	{
		return Vector4(m[col], m[col + 4], m[col + 8], m[col + 12]);
	}

	inline
		void Matrix44::SetRow3(int row, const Vector3& val)
	{
		int ind			= row * 4;
		m[ind]			= val.x;
		m[ind + 1]		= val.y;
		m[ind + 2]		= val.z;
	}
	inline
		Vector3 Matrix44::GetRow3(int row) const
	{
		int ind			= row * 4;
		return Vector3(m[ind], m[ind + 1], m[ind + 2]);
	}
	inline
		void Matrix44::SetRow4(int row, const Vector4& val)
	{
		int ind			= row * 4;
		m[ind]			= val.x;
		m[ind + 1]		= val.y;
		m[ind + 2]		= val.z;
		m[ind + 3]		= val.w;
	}
	inline
		Vector4 Matrix44::GetRow4(int row) const
	{
		int ind			= row * 4;
		return Vector4(m[ind], m[ind + 1], m[ind + 2], m[ind + 3]);
	}

	inline
		const Matrix44& Matrix44::operator-=(const Matrix44& rhs)
	{
		*this += (-rhs);
		return *this;
	}
	inline
		bool Matrix44::IsIdentity() const
	{
		return m11 == 1 && m12 == 0 && m13 == 0 && m14 == 0 &&
			m21 == 0 && m22 == 1 && m23 == 0 && m24 == 0 &&
			m31 == 0 && m32 == 0 && m33 == 1 && m34 == 0 &&
			m41 == 0 && m42 == 0 && m43 == 0 && m44 == 1; 
	}

	inline
		Matrix44 Matrix44::operator+()const
	{
		return *this;
	}
	inline
		Matrix44 Matrix44::operator-()const
	{
		Matrix44 ret;
		for(int i = 0; i < 16; ++i)
		{
			ret.m[i] = -m[i];
		}
		return ret;
	}
	inline
		const Matrix44& Matrix44::operator+=(const Matrix44& rhs)
	{
		for(int i = 0; i < 16; ++i)
		{
			m[i] += rhs.m[i];
		}
		return *this;
	}

	inline
		const Matrix44& Matrix44::operator/=(Real s)
	{
		*this *= (Real(1) / s);
		return *this;
	}
	inline
		const Matrix44& Matrix44::operator*=(Real s)
	{
		for(int i = 0; i < 16; ++i)
		{
			m[i] *= s;
		}
		return *this;
	}

	inline
		Real& Matrix44::operator()(int i, int j)
	{
		return m[i * 4 + j];
	}
	inline
		const Real& Matrix44::operator()(int i, int j) const
	{
		return m[i * 4 + j];
	}
	inline
		void Matrix44::MakeIdentity()
	{
		m11 = 1;
		m12 = 0;
		m13 = 0;
		m14 = 0;

		m21 = 0;
		m22 = 1;
		m23 = 0;
		m24 = 0;

		m31 = 0;
		m32 = 0;
		m33 = 1;
		m34 = 0;

		m41 = 0;
		m42 = 0;
		m43 = 0;
		m44 = 1;
	}

	
	inline
		Matrix44 operator+(const Matrix44& lhs, const Matrix44& rhs)
	{
		Matrix44 ret;
		for(int i = 0; i < 16; ++i)
		{
			ret.m[i] = lhs.m[i] + rhs.m[i];
		}
		return ret;
	}
	inline 
		Matrix44 operator-(const Matrix44& lhs, const Matrix44& rhs)
	{
		return lhs + (-rhs);
	}
	inline
		Matrix44 operator*(Real s, const Matrix44& m)
	{
		Matrix44 ret = m;
		ret *= s;
		return ret;
	}
	inline 
		Matrix44 operator*(const Matrix44& m, Real s)
	{
		return s * m;
	}

	inline 
		bool operator==(const Matrix44& lhs, const Matrix44& rhs)
	{
		for(int i = 0; i < 16; ++i)
		{
			if(lhs.m[i] != rhs.m[i])
				return false;
		}
		return true;
	}
	inline 
		bool operator!=(const Matrix44& lhs, const Matrix44& rhs)
	{
		return !(lhs == rhs);
	}

	inline
		Matrix44::Matrix44(void)
	{
		m11 = 0;
		m12 = 0;
		m13 = 0;
		m14 = 0;

		m21 = 0;
		m22 = 0;
		m23 = 0;
		m24 = 0;

		m31 = 0;
		m32 = 0;
		m33 = 0;
		m34 = 0;

		m41 = 0;
		m42 = 0;
		m43 = 0;
		m44 = 0;
	}

	inline
		Matrix44::Matrix44(Real _m11, Real _m12, Real _m13, Real _m14,
		Real _m21, Real _m22, Real _m23, Real _m24,
		Real _m31, Real _m32, Real _m33, Real _m34,
		Real _m41, Real _m42, Real _m43, Real _m44)
	{
		m11 = _m11;
		m12 = _m12;
		m13 = _m13;
		m14 = _m14;

		m21 = _m21;
		m22 = _m22;
		m23 = _m23;
		m24 = _m24;

		m31 = _m31;
		m32 = _m32;
		m33 = _m33;
		m34 = _m34;

		m41 = _m41;
		m42 = _m42;
		m43 = _m43;
		m44 = _m44;
	}

	inline
		Matrix44::~Matrix44(void)
	{
	}
}

#ifdef _D3DX9_IMPL_
#include <math/details/d3d9x/math_matrix44.inl>
#endif

#ifdef _XNAMATH_IMPL_
#include <math/details/xnamath/math_matrix44.inl>
#endif



#endif