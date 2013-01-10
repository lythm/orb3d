#pragma once

namespace engine
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

	};
}