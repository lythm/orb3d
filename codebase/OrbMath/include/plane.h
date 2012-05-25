#pragma once

#include <orbmathtypes.h>
#include <vector3.h>
#include <alg.h>
namespace math
{
	class plane
	{
	public:
		plane(void);
		~plane(void);

		plane(real _a, real _b, real _c, real _d);
		plane(const vector3& n, real d);
		plane(const vector3& p1, const vector3& p2, const vector3& p3);

		void	build(const vector3& p1, const vector3& p2, const vector3& p3);
		void	build(const vector3& n, const vector3& p);

		real	pointDist(const vector3& p) const;

		union
		{
			struct
			{
				real	a;
				real	b;
				real	c;
				real	d;
			};
			struct
			{
				vector3	normal;
				real	dist;
			};
			real		v[4];
		};
	};


	inline
		plane::plane(void)
	{
		a = b = c = d = real(0);
	}

	inline
		plane::plane(real _a, real _b, real _c, real _d)
	{
		a = _a;
		b = _b;
		c = _c;
		d = _d;
	}
	inline
		plane::plane(const vector3& n, real d)
	{
		normal	= n;
		dist	= d;
	}
	inline
		plane::~plane(void)
	{
	}
	inline
		plane::plane(const vector3& p1, const vector3& p2, const vector3& p3)
	{
		build(p1, p2, p3);
	}
	inline
		void plane::build(const vector3& p1, const vector3& p2, const vector3& p3)
	{
		normal = cross((p2 - p1).getNormalized(), (p3 - p1).getNormalized());
		d = -dot(normal.getNormalized(), p1);
	}
	inline
		void plane::build(const vector3& n, const vector3& p)
	{
		normal = n;
		dist = -dot(n, p);
	}
	inline
		real plane::pointDist(const vector3& p) const
	{
		return d + dot(normal, p);
	}

}