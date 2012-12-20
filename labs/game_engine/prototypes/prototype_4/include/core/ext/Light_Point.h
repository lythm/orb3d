
#pragma once


namespace engine
{
	class EXPORT_CLASS Light_Point : public GameObjectComponent
	{
	public:
		Light_Point(void);
		virtual ~Light_Point(void);

		void										Update();
		void										SetRenderSystem(RenderSystemPtr pRS);
		PointLightPtr								GetLight();

		static Light_PointPtr						CreateComponent();


	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderSystemPtr								m_pRS;
		PointLightPtr								m_pLight;
	};

}