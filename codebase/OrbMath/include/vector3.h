#pragma once

#include <orbmathtypes.h>

namespace math
{
	class vector3
	{
	public:
		vector3(void);
		vector3(real _x, real _y, real _z);
		~vector3(void);

		real length() const;
		void normalize();
		vector3 getNormalized() const;

		vector3 operator +() const;
		vector3 operator -() const;

		const vector3& operator += (const vector3& rhw);
		const vector3& operator -= (const vector3& rhw);

		const vector3& operator *= (real s);
		const vector3& operator /= (real s);

		real operator[](int ind) const;
		real& operator[](int ind);
		
		union
		{
			struct
			{
				real	x;
				real	y;
				real	z;
			};
			real		v[3];
		};
	};

	inline
		vector3::vector3(void)
	{
		x = y = z = real(0);
	}

	inline
		vector3::vector3(real _x, real _y, real _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	inline
		vector3::~vector3(void)
	{
	}

	inline
		real vector3::length() const
	{
		return sqrt(x * x + y * y + z * z);
	}
	inline 
		void vector3::normalize()
	{
		real len = length();
		x /= len;
		y /= len;
		z /= len;
	}
	inline 
		vector3 vector3::getNormalized() const
	{
		vector3 ret(*this);
		ret.normalize();
		return ret;
	}

	inline
		vector3 vector3::operator +() const
	{
		return *this;
	}
	inline
		vector3 vector3::operator -() const
	{
		return vector3(-x, -y, -z);
	}

	inline
		const vector3& vector3::operator += (const vector3& rhw)
	{
		x += rhw.x;
		y += rhw.y;
		z += rhw.z;
		return *this;
	}
	inline
		const vector3& vector3::operator -= (const vector3& rhw)
	{
		x -= rhw.x;
		y -= rhw.y;
		z -= rhw.z;
		return *this;
	}

	inline real vector3::operator[](int ind) const
	{
		return v[ind];
	}
	inline real& vector3::operator[](int ind)
	{
		return v[ind];
	}
	inline
		const vector3& vector3::operator *= (real s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	inline
		const vector3& vector3::operator /= (real s)
	{
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}
	inline 
		bool operator == (const vector3& lhw, const vector3& rhw)
	{
		return lhw.x == rhw.x && lhw.y == rhw.y && lhw.z == rhw.z;
	}
	inline 
		bool operator != (const vector3& lhw, const vector3& rhw)
	{
		return !(lhw == rhw);
	}

	
	inline vector3 operator -(const vector3& lhw, const vector3& rhw)
	{
		vector3 r = lhw;
		r -= rhw;
		return r;
	}
	inline vector3 operator +(const vector3& lhw, const vector3& rhw)
	{
		vector3 r = lhw;
		r += rhw;
		return r;
	}
	inline
		real dot(const vector3& v1, const vector3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	inline
		vector3 cross(const vector3& v1, const vector3& v2)
	{
		return vector3(v1.y * v2.z - v1.z * v2.y, 
						v1.z * v2.x - v1.x * v2.z,
						v1.x * v2.y - v1.y * v2.x);
	}
	inline vector3 operator*(const vector3& lhw, real rhw)
	{
		vector3 r = lhw;
		r *= rhw;
		return r;
	}
	inline vector3 operator*(real lhw, const vector3& rhw)
	{
		return rhw * lhw;
	}
	
}