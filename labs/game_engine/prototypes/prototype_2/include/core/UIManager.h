#pragma once


namespace engine
{
	class UIManager
	{
	public:
		UIManager(void);
		virtual ~UIManager(void);


		void									Update();
		void									Render();
	};


}