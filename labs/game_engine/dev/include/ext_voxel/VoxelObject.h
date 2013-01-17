#pragma once

namespace ld3d
{
	class VoxelObject : public GameObjectComponent
	{
	public:
		VoxelObject(GameObjectManagerPtr pManager);
		virtual ~VoxelObject(void);

		const Version&								GetVersion() const;

	private:
		bool										OnAttach();
		void										OnDetach();
	};


}
