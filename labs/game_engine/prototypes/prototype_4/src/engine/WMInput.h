#pragma once



namespace engine
{
	class WMInput : public Sys_Input
	{
	public:
		WMInput(void);
		virtual ~WMInput(void);


		bool												Initialize(void* app_handle);
		void												Release();
		void												Update();

		
		const KeyState&										GetKeyState();
		const MouseState&									GetMouseState();

		void												ProcessMessage(MSG& msg);

	private:
		KeyState											m_keyState;
		MouseState											m_mouseState;
	};


}