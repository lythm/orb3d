#pragma once

namespace engine
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
