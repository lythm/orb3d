#pragma once

namespace engine
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

	};
}
