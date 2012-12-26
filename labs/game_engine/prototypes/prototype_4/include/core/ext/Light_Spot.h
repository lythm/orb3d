#pragma once


namespace engine
{
	class EXPORT_CLASS Light_Spot : public GameObjectComponent
	{
	public:
		Light_Spot(void);
		virtual ~Light_Spot(void);

		void										Update();
		void										SetRenderSystem(RenderSystemPtr pRS);
		SpotLightPtr								GetLight();

	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderSystemPtr								m_pRS;
		SpotLightPtr								m_pLight;
	};


}