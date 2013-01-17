#pragma once

namespace ld3d
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

		void										Generate();
		const Version&								GetVersion() const;
	private:
		bool										OnAttach();
		void										OnDetach();

		void										RebuildWorld();
		void										DestroyWorld();

	private:
		int											m_blockSize;
		int											m_worldWidth;
		int											m_worldHeight;

		std::vector<VoxelBlockPtr>					m_blocks;
	};
}
