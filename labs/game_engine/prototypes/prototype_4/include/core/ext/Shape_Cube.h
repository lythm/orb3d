#pragma once

namespace engine
{
	class EXPORT_CLASS Shape_Cube: public GameObjectComponent
	{
	public:
		Shape_Cube(GameObjectManagerPtr pManager);
		virtual ~Shape_Cube(void);

		void										Update();
	private:
		bool										OnAttach();
		void										OnDetach();
	private:
		
	};


}
