#pragma once


namespace ld3d
{
	class EXPORT_CLASS Light_Spot : public GameObjectComponent
	{
	public:
		Light_Spot(GameObjectManagerPtr pManager);
		virtual ~Light_Spot(void);

		void										Update();
		SpotLightPtr								GetLight();

	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderSystemPtr								m_pRS;
		SpotLightPtr								m_pLight;
	};


}