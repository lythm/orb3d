#pragma once


namespace ld3d
{
	class Sys_Sound
	{
	public:
		Sys_Sound(void){}
		virtual ~Sys_Sound(void){}

		virtual bool								Initialize()											= 0;
		virtual void								Release()												= 0;
	};
}
