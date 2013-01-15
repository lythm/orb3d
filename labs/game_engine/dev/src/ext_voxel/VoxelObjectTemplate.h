#pragma once
namespace engine
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