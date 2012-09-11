#ifndef __MATH_AABBOX_H__
#define __MATH_AABBOX_H__
#pragma once

#ifndef __MATH_VECTOR3_H__
#include <math/math_vector3.h>
#endif



namespace math
{
	class AABBox
	{
	public:
		AABBox(const Vector3& max_coord, const Vector3& min_coord);
		AABBox();

		~AABBox(void);

		const Vector3&			GetCenter() const;
		const Vector3&			GetMaxCoord() const;
		const Vector3&			GetMinCoord() const;

		void					SetMaxCoord(const Vector3& max_coord);
		void					SetMinCoord(const Vector3& min_coord);
		void					Make(const Vector3& max_coord, const Vector3& min_coord);

		void					Merge(const AABBox& box);

		const AABBox&			operator&=(const AABBox& box);

		bool					IsValid() const;

	private:
		void					UpdateValid();
		void					UpdateCenter();

		bool					m_bValid;
		Vector3					m_max;
		Vector3					m_min;
		Vector3					m_center;
	};

	inline
		AABBox operator&(const AABBox& lhs, const AABBox& rhs)
	{
		AABBox box = lhs;
		box &= rhs;
		return box;
	}

	inline
		AABBox::AABBox(void) : m_max(0, 0, 0), m_min(0, 0, 0)
	{
		UpdateValid();
		UpdateCenter();
	}
	inline
		AABBox::AABBox(const Vector3& max_coord, const Vector3& min_coord) : m_max(max_coord), m_min(min_coord)
	{
		UpdateValid();
		UpdateCenter();
	}
	inline
		AABBox::~AABBox(void)
	{
	}
	inline
		void AABBox::UpdateCenter()
	{
		m_center = (m_max + m_min) * 0.5f;
	}
	inline
		const Vector3& AABBox::GetCenter() const
	{
		return m_center;
	}
	inline
		const Vector3& AABBox::GetMaxCoord() const
	{
		return m_max;
	}
	inline
		const Vector3& AABBox::GetMinCoord() const
	{
		return m_min;
	}
	inline
		void AABBox::SetMaxCoord(const Vector3& max_coord)
	{
		m_max = max_coord;
		UpdateValid();
		UpdateCenter();
	}
	inline
		void AABBox::SetMinCoord(const Vector3& min_coord)
	{
		m_min = min_coord;
		UpdateValid();
		UpdateCenter();
	}
	inline
		void AABBox::Make(const Vector3& max_coord, const Vector3& min_coord)
	{
		m_max = max_coord;
		m_min = min_coord;
		UpdateValid();
		UpdateCenter();
	}
	inline
		void AABBox::Merge(const AABBox& box)
	{
		m_max.x = m_max.x < box.m_max.x ? box.m_max.x : m_max.x;
		m_max.y = m_max.y < box.m_max.y ? box.m_max.y : m_max.y;
		m_max.z = m_max.z < box.m_max.z ? box.m_max.z : m_max.z;

		m_min.x = m_min.x > box.m_min.x ? box.m_min.x : m_min.x;
		m_min.y = m_min.y > box.m_min.y ? box.m_min.y : m_min.y;
		m_min.z = m_min.z > box.m_min.z ? box.m_min.z : m_min.z;

		UpdateValid();
		UpdateCenter();
	}
	inline
		const AABBox& AABBox::operator&=(const AABBox& box)
	{
		if(this == &box)
			return *this;
		Merge(box);
		return *this;
	}
	inline
		bool AABBox::IsValid() const
	{	
		return m_bValid;
	}
	inline
		void AABBox::UpdateValid()
	{
		if( m_max.x < m_min.x ||
			m_max.y < m_min.y ||
			m_max.z < m_min.z )

		{
			m_bValid = false;
		}
		m_bValid = true;
	}
}

#endif
