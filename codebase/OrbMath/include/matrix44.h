#pragma once

#include <orbmathtypes.h>
#include <memory>

namespace math
{
	class matrix44
	{
	public:
		matrix44(void);
		~matrix44(void);

		matrix44(	real _m11, real _m12, real _m13, real _m14, 
			real _m21, real _m22, real _m23, real _m24,
			real _m31, real _m32, real _m33, real _m34,
			real _m41, real _m42, real _m43, real _m44);

		void	identity();
		void	zero();
		void	transpose();
		void	invert();

		real& operator() (int row, int col);
		real operator() (int row, int col) const;

		const matrix44& operator+=(const matrix44& other);
		const matrix44& operator-=(const matrix44& other);
		const matrix44& operator*=(const matrix44& other);

		bool isIdentity() const;
		matrix44 getTranspose() const;
		matrix44 getInverse() const;

		real det() const;
		union
		{
			struct	
			{
				real	m11,
						m12,
						m13,
						m14,
						m21,
						m22,
						m23,
						m24,
						m31,
						m32,
						m33,
						m34,
						m41,
						m42,
						m43,
						m44;
			};		
			real		v[16];
		};



		static matrix44 buildLookAtLH(const vector3& eye, const vector3& at, const vector3& up);
		static matrix44 buildPerspectiveFovLH(real fov, real aspect, real zn, real zf);
	//	static matrix44 buildRotationAxis();
	};

	inline
	matrix44 operator*(const matrix44& m1, const matrix44& m2)
	{
		matrix44 ret;
		int i,j,k;
		
		for(i = 0; i < 4; i++) 
		{
			for(j = 0; j < 4; j++) 
			{
				for(k = 0; k < 4; k++) 
				{
					ret.v[i * 4 + j] += m1.v[i * 4 + k]*m2.v[k * 4 + j];
				}
			}
		}
		return ret;
	}

	inline 
		bool operator ==(const matrix44& m1, const matrix44& m2)
	{
		for(int i = 0; i < 16; ++i)
		{
			if(m1.v[i] != m2.v[i])
				return false;
		}
		return true;
	}
	inline
		bool operator !=(const matrix44& m1, const matrix44& m2)
	{
		return !(m1 == m2);
	}


	inline	
		matrix44::matrix44(void)
	{
		identity();
	}
	inline
		matrix44::matrix44(	real _m11, real _m12, real _m13, real _m14, 
		real _m21, real _m22, real _m23, real _m24,
		real _m31, real _m32, real _m33, real _m34,
		real _m41, real _m42, real _m43, real _m44)
	{
		m11 = _m11, m12 = _m12, m13 = _m13, m14 = _m14, 
			m21 = _m21, m22 = _m22, m23 = _m23, m24 = _m24,
			m31 = _m31, m32 = _m32, m33 = _m33, m34 = _m34,
			m41 = _m41, m42 = _m42, m43 = _m43, m44 = _m44;
	}
	inline
		matrix44::~matrix44(void)
	{
	}

	inline
		void matrix44::identity()
	{
		zero();
		m11 = m22 = m33 = m44 = 1.0f;
	}
	inline
		void matrix44::zero()
	{
		for(int i = 0; i < 16; ++i)
		{
			v[i] = real(0);
		}
	}
	inline
		real& matrix44::operator() (int row, int col)
	{
		return v[4 * (row) + col ];
	}
	inline
		real matrix44::operator() (int row, int col) const
	{
		return v[4 * (row) + col ];
	}
	inline
		const matrix44& matrix44::operator+=(const matrix44& other)
	{
		for(int i = 0; i < 16; ++i)
		{
			v[i] += other.v[i];
		}
		return *this;
	}
	inline
		const matrix44& matrix44::operator-=(const matrix44& other)
	{
		for(int i = 0; i < 16; ++i)
		{
			v[i] -= other.v[i];
		}
		return *this;
	}

	inline
		const matrix44& matrix44::operator*=(const matrix44& other)
	{
		*this = *this * other;
		return *this;
	}

	inline
		bool matrix44::isIdentity() const
	{
		return	m11 == 1.0f && m12 == 0.0f && m13 == 0.0f && m14 == 0.0f &&
				m21 == 0.0f && m22 == 1.0f && m23 == 0.0f && m24 == 0.0f &&
				m31 == 0.0f && m32 == 0.0f && m33 == 1.0f && m34 == 0.0f &&
				m41 == 0.0f && m42 == 0.0f && m43 == 0.0f && m44 == 1.0f;
	}
	inline
		void matrix44::transpose()
	{
		for(int i = 0; i < 4; ++i)
		{
			for(int j = 0; j < 4; ++j)
			{
				std::swap(v[i * 4 + j], v[j * 4 + i]);
			}
		}
	}
	inline
		void matrix44::invert()
	{
		real d = det();
	
		if (abs(d) < EPSILON)
		{
			identity();
		}
		else
		{
			d = 1.f / d;

			matrix44 temp;
			temp.m11 = ( d * ((m22 * m33) - (m23 * m32)));
			temp.m12 = (-d * ((m12 * m33) - (m13 * m32)));
			temp.m13 = ( d * ((m12 * m23) - (m13 * m22)));
			temp.m14 = 0.0f;

			temp.m21 = (-d * ((m21 * m33) - (m23 * m31)));
			temp.m22 = ( d * ((m11 * m33) - (m13 * m31)));
			temp.m23 = (-d * ((m11 * m23) - (m13 * m21)));
			temp.m24 = 0.0f;

			temp.m31 = ( d * ((m21 * m32) - (m22 * m31)));
			temp.m32 = (-d * ((m11 * m32) - (m12 * m31)));
			temp.m33 = ( d * ((m11 * m22) - (m12 * m21)));
			temp.m34 = 0.0f;

			temp.m41 = -((m41 * temp.m11) + (m42 * temp.m21) + (m43 * temp.m31));
			temp.m42 = -((m41 * temp.m12) + (m42 * temp.m22) + (m43 * temp.m32));
			temp.m43 = -((m41 * temp.m13) + (m42 * temp.m23) + (m43 * temp.m33));
			temp.m44 = 1.0f;
			*this = temp;
		}
	}

	inline
		real matrix44::det() const
	{
		return ((m11 * ((m22 * m33) - (m23 * m32))) -
			(m12 * ((m21 * m33) - (m23 * m31))) +
			(m13 * ((m21 * m32) - (m22 * m31))));
	}
	inline
		matrix44 matrix44::getTranspose() const
	{
		matrix44 ret(*this);
		ret.transpose();
		return ret;
	}
	inline
		matrix44 matrix44::getInverse() const
	{
		matrix44 ret(*this);
		ret.invert();
		return ret;
	}

	inline
		matrix44 matrix44::buildLookAtLH(const vector3& eye, const vector3& at, const vector3& up)
	{
		matrix44 mat;
		mat.zero();

		vector3 zaxis = (at - eye).getNormalized();
		vector3 xaxis = (cross(up, zaxis)).getNormalized();
		vector3 yaxis = cross(zaxis, xaxis);

		mat.m11 = xaxis.x;
		mat.m12 = yaxis.x;
		mat.m13 = zaxis.x;
		mat.m14 = 0;

		mat.m21 = xaxis.y;
		mat.m22 = yaxis.y;
		mat.m23 = zaxis.y;
		mat.m24 = 0;

		mat.m31 = xaxis.z;
		mat.m32 = yaxis.z;
		mat.m33 = zaxis.z;
		mat.m34 = 0;


		mat.m41 = -dot(xaxis, eye);
		mat.m42 = -dot(yaxis, eye);
		mat.m43 = -dot(zaxis, eye);
		mat.m44 = 1;

		return mat;
	}

	inline
		matrix44 matrix44::buildPerspectiveFovLH(real fov, real aspect, real zn, real zf)
	{

		// xScale     0          0               0
		// 0        yScale       0               0
		// 0          0       zf/(zf-zn)         1
		// 0          0       -zn*zf/(zf-zn)     0
		// where:
		// yScale = cot(fovY/2)
		//
		// xScale = yScale / aspect ratio




		matrix44 mat;
		mat.zero();

		real ys = 1.0f / tan(fov / 2.0f);
		real xs = ys / aspect;

		
		//real t = real(tan(fov / 2.0));

		//real h = real(1.0) / t;
		//real w = real(1.0) / aspect * h;

		mat.m11 = xs;
		mat.m22 = ys;
		mat.m33 = zf / (zf - zn);
		mat.m34 = 1;
		mat.m43 = -zn * zf / (zf - zn);

		return mat;
	}
}