#pragma once


namespace ld3d
{

	class EXPORT_CLASS Scene
	{
	public:
		Scene(GameObjectManagerPtr pManager);
		virtual ~Scene(void);

		GameObjectPtr					Root();
		void							Reset();
		void							Release();
		void							Update();

		bool							Serialize(DataStream* pStream);
		bool							UnSerialize(DataStream* pStream);
	private:

		bool							SerializeObject(GameObjectPtr pObj, DataStream* pStream);
		bool							UnSerializeObject(GameObjectPtr pObj, DataStream* pStream);
	private:


		GameObjectManagerPtr			m_pObjectManager;
		GameObjectPtr					m_pRoot;
	};
}
