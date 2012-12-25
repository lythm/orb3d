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

		static Light_SpotPtr						CreateComponent();


	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderSystemPtr								m_pRS;
		SpotLightPtr								m_pLight;
	};


}