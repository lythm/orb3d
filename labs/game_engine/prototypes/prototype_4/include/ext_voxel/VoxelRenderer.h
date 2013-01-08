#pragma once

namespace engine
{
	class VoxelRenderer : public GameObjectComponent
	{
	public:
		VoxelRenderer(GameObjectManagerPtr pManager);
		virtual ~VoxelRenderer(void);

		void										Update();
		
	private:
		bool										OnAttach();
		void										OnDetach();

	private:

	};
}
