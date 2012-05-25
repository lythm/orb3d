#pragma once
#include <vector3.h>

namespace math
{
	class AABBox
	{
	public:
		AABBox(const vector3& min, const vector3& max);
		AABBox();
		
		~AABBox();

		const vector3& getMax() const
		{
			return m_max;
		}
		const vector3& getMin() const
		{
			return m_min;
		}

		void build(const vector3& min, const vector3& max);
		void setMax(const vector3& max);
		void setMin(const vector3& min);
		bool isValid() const;

		void combine(const AABBox& box);

		void setValid(bool bValid){m_bInvalid = !bValid;}
		
		const math::vector3& getCenter() const{return m_center;}
	private:
		void updateCenter();
		void updateValid();

	private:
		vector3		m_min;
		vector3		m_max;
		vector3		m_center;
		bool		m_bInvalid;
	};
}



namespace math
{
	inline
	AABBox::AABBox()
	{
		m_bInvalid = true;
	}
	inline
	AABBox::AABBox(const vector3& min, const vector3& max)
	{
		build(min, max);
	}
	inline
	bool AABBox::isValid() const
	{
		return !m_bInvalid;
	}
	inline
	AABBox::~AABBox()
	{
	}
	
	inline
	void AABBox::build(const vector3& min, const vector3& max)
	{
		m_min = min;
		m_max = max;
		updateValid();
		updateCenter();
	}
	inline
	void AABBox::setMax(const vector3& max)
	{
		m_max = max;
		updateValid();
		updateCenter();
	}
	inline
	void AABBox::setMin(const vector3& min)
	{
		m_min = min;
		updateValid();
		updateCenter();
	}
	inline
	void AABBox::updateValid()
	{
		if(m_min.x >= m_max.x || m_min.y >= m_max.y || m_min.z >= m_max.z)
			m_bInvalid = true;
		else
			m_bInvalid = false;
	}
	inline
	void AABBox::combine(const AABBox& box)
	{
		if(isValid() == false)
		{
			*this = box;
			return;
		}
		if(m_min.x > box.m_min.x)	m_min.x = box.m_min.x;
		if(m_min.y > box.m_min.y)	m_min.y = box.m_min.y;
		if(m_min.z > box.m_min.z)	m_min.z = box.m_min.z;

		if(m_max.x < box.m_max.x)	m_max.x = box.m_max.x;
		if(m_max.y < box.m_max.y)	m_max.y = box.m_max.y;
		if(m_max.z < box.m_max.z)	m_max.z = box.m_max.z;

		updateValid();
		updateCenter();
	}
	inline
	void AABBox::updateCenter()
	{
		vector3 corners[8] = 
		{
			vector3(m_min.x, m_min.y, m_min.z),
			vector3(m_max.x, m_min.y, m_min.z),
			vector3(m_min.x, m_max.y, m_min.z),
			vector3(m_max.x, m_max.y, m_min.z),
			vector3(m_min.x, m_min.y, m_max.z),
			vector3(m_max.x, m_min.y, m_max.z),
			vector3(m_min.x, m_max.y, m_max.z),
			vector3(m_max.x, m_max.y, m_max.z),
		};

		m_center.x = m_center.y = m_center.z = 0;
		for(int i = 0; i < 8; ++i)
		{
			m_center += corners[i];
		}
		m_center /= 8.0f;
	}
}