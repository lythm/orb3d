#pragma once

namespace ld3d
{
	class VoxelWorldRenderer : public GameObjectComponent
	{
	public:
		VoxelWorldRenderer(GameObjectManagerPtr pManager);
		virtual ~VoxelWorldRenderer(void);

		void										Update();
		
	private:
		bool										OnAttach();
		void										OnDetach();

	private:

		VoxelWorldRenderDataPtr						m_pRenderData;
	};
}
