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

		const int&									GetBlockSize();
		void										SetBlockSize(const int& blockSize);

		const int&									GetWorldHeight();
		void										SetWorldHeight(const int& h);

		const int&									GetWorldWidth();
		void										SetWorldWidth(const int& w);

	private:
		bool										OnAttach();
		void										OnDetach();

		void										RebuildWorld();
	private:
		int											m_blockSize;
		int											m_worldWidth;
		int											m_worldHeight;
	};
}
