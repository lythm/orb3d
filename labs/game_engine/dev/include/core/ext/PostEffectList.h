#pragma once

namespace ld3d
{
	class PostEffectList : public GameObjectComponent
	{
	public:
		PostEffectList(GameObjectManagerPtr pManager);
		virtual ~PostEffectList(void);


	private:
		bool										OnAttach();
		void										OnDetach();

	private:
		PostEffect_SSAOPtr							m_pSSAO;
		PostEffect_GaussianBlurPtr					m_pGBlur;
	};
}
