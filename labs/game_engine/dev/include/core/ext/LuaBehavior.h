#pragma once

namespace engine
{
	class LuaBehavior : public GameObjectComponent
	{
	public:
		LuaBehavior(GameObjectManagerPtr pManager);
		virtual ~LuaBehavior(void);

		void						Update();
		
	private:
		bool						OnAttach();
		void						OnDetach();
	private:

	};


}