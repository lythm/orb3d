#pragma once


namespace engine
{
	class SceneManager
	{
	public:
		SceneManager(void);
		virtual ~SceneManager(void);


		bool											Initialize(Sys_GraphicsPtr pGraphics);
		void											Release();
		void											Update();
		void											Render();


	private:
		Sys_GraphicsPtr									m_pGraphics;
	};


}