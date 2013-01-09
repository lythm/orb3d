#pragma once

namespace engine
{
	class GameObjectTemplate
	{
	public:
		GameObjectTemplate(GameObjectManagerPtr pManager);
		virtual ~GameObjectTemplate(void);

		const std::wstring&				GetName();
		void							SetName(const std::wstring& name);

		GameObjectPtr					CreateGameObject();

		bool							CreateFromGameObject(GameObjectPtr pObj);
		void							Release();

		bool							Load(DataStreamPtr pStream);
	private:
		std::wstring					m_name;

	private:
		DataStreamPtr					m_pData;
	};
}
