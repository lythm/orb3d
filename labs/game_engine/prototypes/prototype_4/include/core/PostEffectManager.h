#pragma once


namespace engine
{
	class PostEffectManager
	{
	public:
		PostEffectManager(void);
		virtual ~PostEffectManager(void);

		bool										Initialize(RenderSystemPtr pRS);
		void										Release();

		void										Render();

		RenderTargetPtr								GetInput();
		RenderTargetPtr								GetOutput();

		int											GetEffectCount();
	private:
		void										SwapRenderTarget();

	private:
		RenderTargetPtr								m_pOutput;
		RenderTargetPtr								m_pInput;

		std::vector<PostEffectPtr>					m_effects;

		RenderSystemPtr								m_pRS;
	};


}