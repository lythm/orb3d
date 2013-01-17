#pragma once


#include "core\ExtPackage.h"

namespace ld3d
{
	class VoxelPackage : public ExtPackage
	{
	public:
		VoxelPackage(CoreApiPtr pCore);
		virtual ~VoxelPackage(void);

		

		const wchar_t*						GetPackageName();
		int									GetClassCount();
		ComponentClass*						GetClassByIndex(int index);

		int									GetTemplateCount();
		GameObjectTemplate*					GetTemplateByIndex(int index);

		void								Release();
	private:
		
		static GameObjectComponentPtr		Create_VoxelWorld(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_VoxelWorldRenderer(GameObjectManagerPtr pManager);

		static GameObjectComponentPtr		Create_VoxelObject(GameObjectManagerPtr pManager);
		static GameObjectComponentPtr		Create_VoxelObjectRenderer(GameObjectManagerPtr pManager);
	private:

		CoreApiPtr							m_pCore;
		std::vector<ComponentClass>			m_classes;
		std::vector<GameObjectTemplate*>	m_tpls;
	};
}
