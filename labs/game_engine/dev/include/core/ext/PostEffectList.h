#pragma once

namespace ld3d
{
	class PostEffectList : public GameObjectComponent
	{
	public:
		PostEffectList(GameObjectManagerPtr pManager);
		virtual ~PostEffectList(void);

		const Version&								GetVersion() const;
	private:
		bool										OnAttach();
		void										OnDetach();

	private:
		PostEffect_SSAOPtr							m_pSSAO;
		PostEffect_GaussianBlurPtr					m_pGBlur;
	};
}
