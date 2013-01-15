#pragma once

namespace ld3d
{
	class EXPORT_CLASS Light_Sky : public GameObjectComponent
	{
	public:
		Light_Sky(GameObjectManagerPtr pManager);
		virtual ~Light_Sky(void);

		void										Update();
		SkyLightPtr									GetLight();


		bool										Serialize(DataStream* pStream);
		bool										UnSerialize(DataStream* pStream);


	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderSystemPtr								m_pRS;
		SkyLightPtr									m_pLight;
	};


}
