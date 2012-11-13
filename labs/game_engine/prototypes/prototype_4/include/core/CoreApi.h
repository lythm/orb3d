#pragma once


namespace engine
{
	class EXPORT_CLASS CoreApi
	{
	public:
		CoreApi(void);
		virtual ~CoreApi(void);

		void											Update();
		bool											Initialize(void* app_handle, int w, int h, G_FORMAT format);
		void											Release();
		void											HandleMessage(MSG& msg);
		
		GameObjectManagerPtr							GetGameObjectManager();
		Sys_GraphicsPtr									GetSysGraphics();
		Sys_InputPtr									GetSysInput();

		void											Render();
		void											AddRenderData(RenderDataPtr pData);
		void											ClearRenderQueue();
	private:
		GameObjectManagerPtr							m_pObjectManager;
		SysManagerPtr									m_pSysManager;
		Sys_GraphicsPtr									m_pSysGraphics;
		Sys_InputPtr									m_pSysInput;

		RenderSystemPtr									m_pRenderSystem;
	};


}
