#pragma once

#include <boost\smart_ptr.hpp>

namespace ld3d
{
	class VoxelWorld;
	class VoxelWorldRenderer;
	class VoxelObject;
	class VoxelObjectRenderer;

	typedef boost::shared_ptr<VoxelWorld>							VoxelWorldPtr;
	typedef boost::shared_ptr<VoxelWorldRenderer>					VoxelWorldRendererPtr;
	typedef boost::shared_ptr<VoxelObject>							VoxelObjectPtr;
	typedef boost::shared_ptr<VoxelObjectRenderer>					VoxelObjectRendererPtr;

	class VoxelWorldRenderData;
	class VoxelBlock;

	typedef boost::shared_ptr<VoxelBlock>							VoxelBlockPtr;
	typedef boost::shared_ptr<VoxelWorldRenderData>					VoxelWorldRenderDataPtr;
		
}
