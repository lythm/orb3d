#pragma once
namespace engine
{
	class DirLightTpl : public GameObjectTemplate
	{
	public:
		DirLightTpl(GameObjectManagerPtr pManager, const std::wstring& name);
		virtual ~DirLightTpl(void);

		GameObjectPtr					CreateGameObject();
		void							Release();
	};


}