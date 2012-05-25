#ifndef __ALG__H__
#define __ALG__H__

#include <orbmathtypes.h>
#include <vector2.h>
#include <vector3.h>
#include <matrix44.h>
#include <sphere.h>
#include <ray.h>
#include <AABBox.h>
namespace math
{
	inline
		real DEG2RAD(real d) 
	{
		return ((d)*PI/real(180));
	}
	inline 
		real RAD2DEG(real r)
	{
		return ((r)*real(180)/PI);
	}

	template <class T>
		inline void clamp(T& value, const T& min, const T& max)
	{
		value = (value < min) ? min : value;
		value = (value > max) ? max : value;
	}
	inline
		void transformPoint(vector3& v, const matrix44& m)
	{
		real x,y,z,w;
		x = v.x * m(0, 0) + v.y * m(1, 0) + v.z * m(2, 0) + m(3, 0);
		y = v.x * m(0, 1) + v.y * m(1, 1) + v.z * m(2, 1) + m(3, 1);
		z = v.x * m(0, 2) + v.y * m(1, 2) + v.z * m(2, 2) + m(3, 2);
		w = v.x * m(0, 3) + v.y * m(1, 3) + v.z * m(2, 3) + m(3, 3);
		v.x = x / w;
		v.y = y / w;
		v.z = z / w;
	}
	inline
		void transformVector(vector3& v, const matrix44& m)
	{
		real x, y, z, w;
		x = v.x * m(0, 0) + v.y * m(1, 0) + v.z * m(2, 0);
		y = v.x * m(0, 1) + v.y * m(1, 1) + v.z * m(2, 1);
		z = v.x * m(0, 2) + v.y * m(1, 2) + v.z * m(2, 2);
		w = v.x * m(0, 3) + v.y * m(1, 3) + v.z * m(2, 3);

		if(abs(w) < EPSILON)
		{
			v.x = x;
			v.y = y;
			v.z = z;
		}
		else
		{
			v.x = x / w;
			v.y = y / w;
			v.z = z / w;
		}
	}

	inline
		bool rayIntersect(const Ray& ray, 
					const math::vector3& p0, 
					const math::vector3& p1, 
					const math::vector3& p2,
					real& t0,
					real& u,
					real& v)
	{
		vector3 e1, e2, p, s, q;
		real t, tmp;

		e1 = p1 - p0;
		e2 = p2 - p0;
		p = cross(ray.dir, e2);
		tmp = dot(p, e1);
		if(tmp > -EPSILON && tmp < EPSILON)
		{
			return false;
		}

		tmp = real(1.0) / tmp;
		s = ray.ori - p0;

		u = tmp * dot(s, p);
		if(u < 0.0 || u > 1.0)
			return false;

		q = cross(s, e1);
		v = tmp * dot(ray.dir, q);

		if(v < 0.0 || v > 1.0)
			return false;

		if(u + v > 1.0)
			return false;

		t = tmp * dot(e2, q);
		if(t < 0)
			return false;

		t0 = t;
		return true;

	}
	inline
		bool rayIntersect(const Ray& ray, 
					const Sphere& sphere, 
					real&	t0)
	{
		real a, b, c, discrm;

		vector3 pMinusC = ray.ori - sphere.center;

		c = dot(pMinusC, pMinusC) - sphere.radius * sphere.radius;
		// ray.m_ori in sphere
		if( c < 0)
			return false;


		a = dot(ray.dir, ray.dir);
		b = 2 * dot(ray.dir, pMinusC);

		discrm = b * b - 4 * a * c;

		if(discrm > 0)
		{
			real t;
			t = (-b - sqrt(discrm)) / (2  * a);
			if(t <= 0)
				return false;

			t0 = t;
			return true;
		}
		else if(discrm == 0)
		{
			real t = -b / ( 2 * a);
			if(t <= 0)
				return false;
			t0 = t;
			return true;
		}
		else
		{
			return false;
		}
	}
	inline
	bool rayIntersect(const Ray& ray, const AABBox& box, real& t0, real& t1)
	{
		t0 = -POS_INF;
		t1 = POS_INF;

		const vector3& minp = box.getMin();
		const vector3& maxp = box.getMax();
		const vector3& p = ray.ori;
		const vector3& d = ray.dir;

		for(int i = 0; i < 3; ++i)
		{
			if(abs(d[i]) < EPSILON)
			{
				if(p[i] < minp[i] || p[i] > maxp[i])
					return false;
			}

			real tnear = (minp[i] - p[i]) / d[i];
			real tfar = (maxp[i] - p[i]) / d[i];

			if(tnear > tfar)
			{
				std::swap(tnear, tfar);
			}
			if(tnear > t0)
			{
				t0 = tnear;
			}
			if(tfar < t1)
			{
				t1 = tfar;
			}
			if(t0 > t1)
			{
				return false;
			}
			if(t1 < 0)
			{
				return false;
			}
		}
			
		return true;
	}
}
#endif