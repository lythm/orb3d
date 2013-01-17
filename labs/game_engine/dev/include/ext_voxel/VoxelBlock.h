#pragma once

namespace ld3d
{
	class VoxelBlock
	{
	public:
		VoxelBlock(void);
		virtual ~VoxelBlock(void);

	private:
		int									m_x;
		int									m_y;
		int									m_z;
	};
}
