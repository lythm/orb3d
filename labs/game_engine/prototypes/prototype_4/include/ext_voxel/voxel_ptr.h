#pragma once

#include <boost\smart_ptr.hpp>

namespace engine
{
	class VoxelWorld;
	class VoxelWorldRenderer;


	typedef boost::shared_ptr<VoxelWorld>							VoxelWorldPtr;
	typedef boost::shared_ptr<VoxelWorldRenderer>					VoxelWorldRendererPtr;

	
}
