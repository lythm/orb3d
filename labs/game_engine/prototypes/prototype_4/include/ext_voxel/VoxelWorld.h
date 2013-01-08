#pragma once

namespace engine
{
	class VoxelWorld : public GameObjectComponent
	{
	public:
		VoxelWorld(GameObjectManagerPtr pManager);
		virtual ~VoxelWorld(void);

		void										Update();
		
		void										AddBlock();
		void										RemoveBlock();

		const float&								GetUnitSize();
		void										SetUnitSize(const float& size);

	private:
		bool										OnAttach();
		void										OnDetach();


	private:
		float										m_unitSize;

	};
}
