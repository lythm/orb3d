
#pragma once


namespace ld3d
{
	class EXPORT_CLASS Light_Point : public GameObjectComponent
	{
	public:
		Light_Point(GameObjectManagerPtr pManager);
		virtual ~Light_Point(void);

		void										Update();
		PointLightPtr								GetLight();

	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderSystemPtr								m_pRS;
		PointLightPtr								m_pLight;
	};

}