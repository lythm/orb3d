#include "voxel_pch.h"
#include "..\..\include\ext_voxel\VoxelWorld.h"
#include "ext_voxel\VoxelBlock.h"


namespace ld3d
{
	VoxelWorld::VoxelWorld(GameObjectManagerPtr pManager) : GameObjectComponent(L"VoxelWorld", pManager)
	{
		m_blockSize				= 1;
		m_worldWidth			= 10;
		m_worldHeight			= 10;

	}


	VoxelWorld::~VoxelWorld(void)
	{
	}
	void VoxelWorld::Update()
	{

	}
	const Version& VoxelWorld::GetVersion() const
	{
		return g_packageVersion;
	}

	bool VoxelWorld::OnAttach()
	{
		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"VoxelWorld");
		{
			pPM->RegisterProperty<int, VoxelWorld>(this,
				L"Block Size",
				&VoxelWorld::GetBlockSize,
				&VoxelWorld::SetBlockSize);

			pPM->RegisterProperty<int, VoxelWorld>(this,
				L"World Width",
				&VoxelWorld::GetWorldWidth,
				&VoxelWorld::SetWorldWidth);

			pPM->RegisterProperty<int, VoxelWorld>(this,
				L"World Height",
				&VoxelWorld::GetWorldHeight,
				&VoxelWorld::SetWorldHeight);
		}
		pPM->End();


		return true;
	}
	void VoxelWorld::DestroyWorld()
	{
		m_blocks.clear();
	}
	const int& VoxelWorld::GetBlockSize()
	{
		return m_blockSize;
	}
	void VoxelWorld::SetBlockSize(const int& blockSize)
	{
		m_blockSize = blockSize;
	}
	void VoxelWorld::OnDetach()
	{
		DestroyWorld();
	}
	void VoxelWorld::AddBlock()
	{
	}
	void VoxelWorld::RemoveBlock()
	{
	}
	const int& VoxelWorld::GetWorldHeight()
	{
		return m_worldHeight;
	}
	void VoxelWorld::SetWorldHeight(const int& h)
	{
		DestroyWorld();
		m_worldHeight = h;
		RebuildWorld();
	}
	const int& VoxelWorld::GetWorldWidth()
	{
		return m_worldWidth;
	}
	void VoxelWorld::SetWorldWidth(const int& w)
	{
		DestroyWorld();
		m_worldWidth = w;
		RebuildWorld();
	}
	void VoxelWorld::RebuildWorld()
	{
		DestroyWorld();

		Generate();
		
	}
	
	void VoxelWorld::Generate()
	{
		for(int i = 0; i < m_worldHeight * m_worldWidth; ++i)
		{
			VoxelBlockPtr pBlock = m_pManager->GetAllocator()->AllocObject<VoxelBlock>();

			m_blocks.push_back(pBlock);
		}
	}
}

