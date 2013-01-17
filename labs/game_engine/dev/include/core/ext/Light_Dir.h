#pragma once

namespace ld3d
{
	class EXPORT_CLASS Light_Dir : public GameObjectComponent
	{
	public:
		Light_Dir(GameObjectManagerPtr pManager);
		virtual ~Light_Dir(void);

		void										Update();
		DirectionalLightPtr							GetLight();

		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version );

		const Version&								GetVersion() const;

	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderSystemPtr								m_pRS;
		DirectionalLightPtr							m_pLight;
	};
}
