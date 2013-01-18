#include "voxel_pch.h"
#include "VoxelPolygonizer.h"

namespace ld3d
{
	VoxelPolygonizer::VoxelPolygonizer(void)
	{
	}


	VoxelPolygonizer::~VoxelPolygonizer(void)
	{
	}
	std::vector<VoxelPolygonizer::Face> VoxelPolygonizer::Polygonize(VoxelWorldPtr pWorld)
	{
		return std::vector<Face>();
	}
	std::vector<VoxelPolygonizer::Face> VoxelPolygonizer::Polygonize(VoxelObjectPtr pObj)
	{
		return std::vector<Face>();
	}
	std::vector<VoxelPolygonizer::Face> VoxelPolygonizer::Polygonize(VoxelBlockPtr pBlock)
	{
		return std::vector<Face>();
	}
}
