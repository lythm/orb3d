#pragma once

namespace engine
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
