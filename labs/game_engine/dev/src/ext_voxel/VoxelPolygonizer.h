#pragma once

namespace ld3d
{
	class VoxelPolygonizer
	{
	public:
		struct Face
		{
			math::Vector3	v[3];
		};

		VoxelPolygonizer(void);
		virtual ~VoxelPolygonizer(void);

		std::vector<Face>				Polygonize(VoxelWorldPtr pWorld);
		std::vector<Face>				Polygonize(VoxelObjectPtr pObj);
		std::vector<Face>				Polygonize(VoxelBlockPtr pBlock);
	};
}
