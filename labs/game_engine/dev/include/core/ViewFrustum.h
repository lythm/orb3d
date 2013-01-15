#pragma once

namespace ld3d
{
	class EXPORT_CLASS ViewFrustum
	{
	public:
		enum
		{
			left_plane,
			right_plane,
			top_plane,
			bottom_plane,
			near_plane,
			far_plane,
			max_planes,
		};

		
		ViewFrustum(void);
		virtual ~ViewFrustum(void);

		void						Update(const math::Matrix44& view, const math::Matrix44& proj);
		bool						IntersectSphere(const math::Sphere& sphere) const;
		bool						IntersectBox(const math::AABBox& box) const;

	private:
		math::Plane					m_planes[max_planes];
	};
}
