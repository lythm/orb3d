#pragma once

#include <orbmathtypes.h>
namespace math
{
	class vector2
	{
	public:
		vector2(void);
		vector2(real _x, real _y);
		~vector2(void);


		real	length() const;
		void	normalize();
		vector2 getNormalized() const;

		vector2			operator +() const;
		vector2			operator -() const;

		const vector2&	operator += (const vector2& rhw);
		const vector2&	operator -= (const vector2& rhw);

		const vector2&	operator *= (real s);
		const vector2&	operator /= (real s);

		union
		{
			struct
			{
				real x;
				real y;
			};
			real	v[2];
		};
	};

	
	inline
		vector2::vector2(void)
	{
		x = y = real(0);
	}
	inline
		vector2::vector2(real _x, real _y)
	{
		x = _x;
		y = _y;
	}
	inline
		vector2::~vector2(void)
	{
	}
	inline
		real vector2::length() const
	{
		return sqrt(x * x + y * y);
	}
	inline
		void vector2::normalize()
	{
		real len = length();
		x /= len;
		y /= len;
	}

	inline
		vector2 vector2::getNormalized() const
	{
		vector2 ret(*this);
		ret.normalize();
		return ret;
	}

	inline
		const vector2& vector2::operator += (const vector2& rhw)
	{
		x += rhw.x;
		y += rhw.y;
		return *this;
	}
	inline
		const vector2&	vector2::operator -= (const vector2& rhw)
	{
		x -= rhw.x;
		y -= rhw.y;
		return *this;
	}

	inline
		const vector2&	vector2::operator *= (real s)
	{
		x *= s;
		y *= s;
		return *this;
	}
	inline
		const vector2&	vector2::operator /= (real s)
	{
		x /= s;
		y /= s;
		return *this;
	}
	inline
		vector2	vector2::operator +() const
	{
		return *this;
	}
	inline
		vector2	vector2::operator -() const
	{
		return vector2(-x, -y);
	}

	inline 
		vector2 operator -(const vector2& lhw, const vector2& rhw)
	{
		vector2 r = lhw;
		r -= rhw;
		return r;
	}
	inline 
		vector2 operator +(const vector2& lhw, const vector2& rhw)
	{
		vector2 r = lhw;
		r += rhw;
		return r;
	}
	inline 
		bool operator == (const vector2& lhw, const vector2& rhw)
	{
		return lhw.x == rhw.x && lhw.y == rhw.y;
	}
	inline 
		bool operator != (const vector2& lhw, const vector2& rhw)
	{
		return !(lhw == rhw);
	}
	inline
		real dot(const vector2& v1, const vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}
}