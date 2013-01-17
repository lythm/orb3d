#pragma once

namespace ld3d
{
	class VoxelWorldRenderer : public GameObjectComponent
	{
	public:
		VoxelWorldRenderer(GameObjectManagerPtr pManager);
		virtual ~VoxelWorldRenderer(void);

		void										Update();
		const Version&								GetVersion() const;
	private:
		bool										OnAttach();
		void										OnDetach();

	private:

		VoxelWorldRenderDataPtr						m_pRenderData;
	};
}
