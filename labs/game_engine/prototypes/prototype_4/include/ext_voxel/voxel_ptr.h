#pragma once

#include <boost\smart_ptr.hpp>

namespace engine
{
	class VoxelWorld;
	class VoxelWorldRenderer;
	class VoxelObject;
	class VoxelObjectRenderer;

	typedef boost::shared_ptr<VoxelWorld>							VoxelWorldPtr;
	typedef boost::shared_ptr<VoxelWorldRenderer>					VoxelWorldRendererPtr;
	typedef boost::shared_ptr<VoxelObject>							VoxelObjectPtr;
	typedef boost::shared_ptr<VoxelObjectRenderer>					VoxelObjectRendererPtr;

	
}
