#ifndef __MATH_INTERSECTIONS_H__
#define __MATH_INTERSECTIONS_H__

#pragma once

#ifndef __MATH_AABBOX_H__
#include <math/math_aabbox.h>
#endif

#ifndef __MATH_PLANE_H__
#include <math/math_plane.h>
#endif

#ifndef __MATH_RAY_H__
#include <math/math_ray.h>
#endif

#ifndef __MATH_ALG_H__
#include <math/math_alg.h>
#endif

namespace math
{
	// intersection test
	enum intersect_ret
	{
		intersect_front			= 0,
		intersect_back,
		intersect_none,
		intersect_inside,
		intersect_outside,
		intersect_intersect,
	};

	inline
		intersect_ret AABBoxIntersectAABBox(const AABBox& lhs, const AABBox& rhs)
	{
		if( lhs.IsValid() == false || rhs.IsValid() == false)
			return intersect_none;

		const Vector3& lmax = lhs.GetMaxCoord();
		const Vector3& lmin = lhs.GetMinCoord();
		const Vector3& rmax = rhs.GetMaxCoord();
		const Vector3& rmin = rhs.GetMinCoord();

		if(lmax.x < rmin.x)
			return intersect_none;
		if(lmax.y < rmin.y)
			return intersect_none;
		if(lmax.z < rmin.z)
			return intersect_none;

		if(lmin.x > rmax.x)
			return intersect_none;
		if(lmin.y > rmax.y)
			return intersect_none;
		if(lmin.z > rmax.z)
			return intersect_none;

		return intersect_intersect;
	}

	inline
		intersect_ret RayIntersectPlane(const Ray& r, const Plane& p, Real& t)
	{
		Real dn = Dot(r.d, p.normal);
		if(dn == 0)
			return intersect_none;
		t = (p.dist - Dot(r.o , p.normal)) / dn;

		return dn < 0 ? intersect_front : intersect_back;
	}
	inline
		intersect_ret RayIntersectPlaneTest(const Ray& r, const Plane& p)
	{
		Real dn = Dot(r.d, p.normal);
		if(dn == 0)
			return intersect_none;

		return dn < 0 ? intersect_front : intersect_back;
	}
	inline
		intersect_ret AABBoxIntersectPlaneTest(const AABBox& box, const Plane& plane)
	{
		Vector3 N(plane.a, plane.b, plane.c);
		Vector3 vmin, vmax;
		const Vector3& bmax = box.GetMaxCoord();
		const Vector3& bmin = box.GetMinCoord();

		for(int i = 0; i < 3; ++i)
		{
			if(N[i] >= 0)
			{
				vmin[i] = bmin[i];
				vmax[i] = bmax[i];
			}
			else
			{
				vmin[i] = bmax[i];
				vmax[i] = bmin[i];
			}
		}

		if((Dot(N, vmin) + plane.d) > 0)
			return intersect_outside;
		if((Dot(N, vmax) + plane.d) < 0)
			return intersect_inside;

		return intersect_intersect;
	}

}

#endif