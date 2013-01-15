#pragma once

namespace engine
{
	class VoxelWorldTemplate : public GameObjectTemplate
	{
	public:
		VoxelWorldTemplate(GameObjectManagerPtr pManager, const std::wstring& name);
		virtual ~VoxelWorldTemplate(void);

		GameObjectPtr					CreateGameObject();
		void							Release();

	};
}