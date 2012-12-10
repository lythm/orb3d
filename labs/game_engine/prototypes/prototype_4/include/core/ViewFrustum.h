#pragma once

namespace engine
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
		bool						IntersectBox(const math::AABBox& box);

	private:
		math::Plane					m_planes[max_planes];
	};
}
