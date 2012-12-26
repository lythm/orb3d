#pragma once

namespace engine
{
	class EXPORT_CLASS Light_Sky : public GameObjectComponent
	{
	public:
		Light_Sky(void);
		virtual ~Light_Sky(void);

		void										Update();
		void										SetRenderSystem(RenderSystemPtr pRS);
		SkyLightPtr									GetLight();

		static Light_SkyPtr							CreateComponent();


	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderSystemPtr								m_pRS;
		SkyLightPtr									m_pLight;
	};


}