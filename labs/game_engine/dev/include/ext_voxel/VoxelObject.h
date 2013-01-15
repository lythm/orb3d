#pragma once

namespace engine
{
	class VoxelObject : public GameObjectComponent
	{
	public:
		VoxelObject(GameObjectManagerPtr pManager);
		virtual ~VoxelObject(void);

	private:
		bool										OnAttach();
		void										OnDetach();
	};


}
