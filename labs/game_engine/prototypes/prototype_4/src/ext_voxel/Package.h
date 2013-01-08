#pragma once


#include "core\ExtPackage.h"

namespace engine
{
	class VoxelPackage : public ExtPackage
	{
	public:
		VoxelPackage(CoreApiPtr pCore);
		virtual ~VoxelPackage(void);

		

		std::wstring						GetPackageName();
		int									GetClassCount();
		ComponentClass*						GetClassByIndex(int index);


	private:
		
		static GameObjectComponentPtr		Create_VoxelData(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_VoxelRenderer(GameObjectManagerPtr pManager);
	private:

		CoreApiPtr							m_pCore;
		std::vector<ComponentClass>			m_classes;
	};
}
