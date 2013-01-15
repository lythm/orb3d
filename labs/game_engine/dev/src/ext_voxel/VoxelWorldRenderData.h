#pragma once

namespace ld3d
{
	class VoxelWorldRenderData
	{
	public:
		VoxelWorldRenderData(void);
		virtual ~VoxelWorldRenderData(void);

		bool													Initialize();
		void													Release();



	private:
		GPUBufferPtr											m_pVertexBuffer;
		GPUBufferPtr											m_pIndexBuffer;
	};
}
