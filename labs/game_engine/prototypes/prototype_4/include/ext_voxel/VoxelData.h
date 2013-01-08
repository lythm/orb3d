#pragma once

namespace engine
{
	class VoxelData : public GameObjectComponent
	{
	public:
		VoxelData(GameObjectManagerPtr pManager);
		virtual ~VoxelData(void);

		void										Update();
		
	private:
		bool										OnAttach();
		void										OnDetach();

	};


}