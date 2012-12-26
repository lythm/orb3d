#pragma once

namespace engine
{
	class EXPORT_CLASS Light_Dir : public GameObjectComponent
	{
	public:
		Light_Dir(void);
		virtual ~Light_Dir(void);

		void										Update();
		void										SetRenderSystem(RenderSystemPtr pRS);
		DirectionalLightPtr							GetLight();

	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		RenderSystemPtr								m_pRS;
		DirectionalLightPtr							m_pLight;
	};
}
