#pragma once
namespace ld3d
{
	class VoxelObjectTemplate : public GameObjectTemplate
	{
	public:
		VoxelObjectTemplate(GameObjectManagerPtr pManager, const std::wstring& name);
		virtual ~VoxelObjectTemplate(void);

		GameObjectPtr					CreateGameObject();
		void							Release();

	};
}