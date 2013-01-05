#pragma once

namespace engine
{
	class EXPORT_CLASS Light_Sky : public GameObjectComponent
	{
	public:
		Light_Sky(GameObjectManagerPtr pManager);
		virtual ~Light_Sky(void);

		void										Update();
		SkyLightPtr									GetLight();

	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderSystemPtr								m_pRS;
		SkyLightPtr									m_pLight;
	};


}
