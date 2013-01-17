#pragma once

namespace ld3d
{
	class VoxelObjectRenderer : public GameObjectComponent
	{
	public:
		VoxelObjectRenderer(GameObjectManagerPtr pManager);
		virtual ~VoxelObjectRenderer(void);

		void										Update();
		const Version&								GetVersion() const;
	private:
		bool										OnAttach();
		void										OnDetach();

	private:

	};
}
