#include "core_pch.h"
#include "..\..\include\core\ViewFrustum.h"


namespace ld3d
{

	ViewFrustum::ViewFrustum(void)
	{
	}

	ViewFrustum::~ViewFrustum(void)
	{
	}
	void ViewFrustum::Update(const math::Matrix44& view, const math::Matrix44& proj)
	{
		math::Matrix44 M = view * proj;

		// left plane
		m_planes[left_plane].a		= M.m14 + M.m11;
		m_planes[left_plane].b		= M.m24 + M.m21;
		m_planes[left_plane].c		= M.m34 + M.m31;
		m_planes[left_plane].d		= M.m44 + M.m41;

		// right plane
		m_planes[right_plane].a		= M.m14 - M.m11;
		m_planes[right_plane].b		= M.m24 - M.m21;
		m_planes[right_plane].c		= M.m34 - M.m31;
		m_planes[right_plane].d		= M.m44 - M.m41;

		// top plane
		m_planes[top_plane].a		= M.m14 - M.m12;
		m_planes[top_plane].b		= M.m24 - M.m22;
		m_planes[top_plane].c		= M.m34 - M.m32;
		m_planes[top_plane].d		= M.m44 - M.m42;

		// bottom plane
		m_planes[bottom_plane].a		= M.m14 + M.m12;
		m_planes[bottom_plane].b		= M.m24 + M.m22;
		m_planes[bottom_plane].c		= M.m34 + M.m32;
		m_planes[bottom_plane].d		= M.m44 + M.m42;

		// near plane
		m_planes[near_plane].a		= M.m13;
		m_planes[near_plane].b		= M.m23;
		m_planes[near_plane].c		= M.m33;
		m_planes[near_plane].d		= M.m43;

		// far plane
		m_planes[far_plane].a		= M.m14 - M.m13;
		m_planes[far_plane].b		= M.m24 - M.m23;
		m_planes[far_plane].c		= M.m34 - M.m33;
		m_planes[far_plane].d		= M.m44 - M.m43;
	}
	bool ViewFrustum::IntersectBox(const math::AABBox& box) const
	{
		int vec_in_cnt;
		int plane_in_cnt = 0;

		math::Vector3 min = box.GetMinCoord();
		math::Vector3 max = box.GetMaxCoord();

		for( int p = 0; p < 6; p++ )
		{
			vec_in_cnt = 0;
			if( m_planes[p].a * min.x +
				m_planes[p].b * min.y +
				m_planes[p].c * min.z +
				m_planes[p].d > 0)
				vec_in_cnt ++;
			if( m_planes[p].a * max.x +
				m_planes[p].b * min.y +
				m_planes[p].c * min.z +
				m_planes[p].d > 0)
				vec_in_cnt ++;
			if( m_planes[p].a * max.x +
				m_planes[p].b * max.y +
				m_planes[p].c * min.z +
				m_planes[p].d > 0)
				vec_in_cnt ++;
			if( m_planes[p].a * min.x +
				m_planes[p].b * max.y +
				m_planes[p].c * min.z +
				m_planes[p].d > 0)
				vec_in_cnt ++;
			if( m_planes[p].a * min.x +
				m_planes[p].b * min.y +
				m_planes[p].c * max.z +
				m_planes[p].d > 0)
				vec_in_cnt ++;
			if( m_planes[p].a * max.x +
				m_planes[p].b * min.y +
				m_planes[p].c * max.z +
				m_planes[p].d > 0)
				vec_in_cnt ++;
			if( m_planes[p].a * max.x +
				m_planes[p].b * max.y +
				m_planes[p].c * max.z +
				m_planes[p].d > 0)
				vec_in_cnt ++;
			if( m_planes[p].a * min.x +
				m_planes[p].b * max.y +
				m_planes[p].c * max.z +
				m_planes[p].d > 0)
				vec_in_cnt ++;
			
			if (vec_in_cnt == 0)
				return false;

			if (vec_in_cnt == 8)
				plane_in_cnt++;
		}

		return true;
		//return (plane_in_cnt == 6) ? 2 : 1;
	}
	bool ViewFrustum::IntersectSphere(const math::Sphere& sphere) const
	{
		return true;
	}
}