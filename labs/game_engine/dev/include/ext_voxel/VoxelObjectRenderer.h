#pragma once

namespace ld3d
{
	class VoxelObjectRenderer : public GameObjectComponent
	{
	public:
		VoxelObjectRenderer(GameObjectManagerPtr pManager);
		virtual ~VoxelObjectRenderer(void);

		void										Update();
		
	private:
		bool										OnAttach();
		void										OnDetach();

	private:

	};
}
