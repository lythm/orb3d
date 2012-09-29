#pragma once

namespace engine
{
	class EXPORT_CLASS GFX
	{
	public:
		GFX(void);
		virtual ~GFX(void);


		virtual void								BeginPass(int& pass)					= 0;
		virtual void								EndPass()								= 0;
		virtual void								ApplyPass()								= 0;


	};


}